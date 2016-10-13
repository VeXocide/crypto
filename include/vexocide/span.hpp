// Copyright Jeroen Habraken 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0122r3.pdf

#ifndef VEXOCIDE_SPAN_HPP
#define VEXOCIDE_SPAN_HPP

#include <vexocide/cstddef.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <exception>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace vexocide {

// [views.constants], constants
constexpr ptrdiff_t dynamic_extent = -1;

// [span], class template span
template <class ElementType, ptrdiff_t Extent = dynamic_extent> class span;

namespace detail {

template <class ElementType, ptrdiff_t Extent> class span_iterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename span<ElementType, Extent>::element_type;
  using difference_type = typename span<ElementType, Extent>::difference_type;
  using pointer = typename span<ElementType, Extent>::pointer;
  using reference = typename span<ElementType, Extent>::reference;

  span_iterator() noexcept : data_(nullptr), span_({}) {}

  reference operator*() const noexcept {
    assert(data_ != nullptr && data_ >= span_.data() &&
           data_ < span_.data() + span_.size());

    return *data_;
  }

  pointer operator->() const noexcept {
    assert(data_ != nullptr && data_ >= span_.data() &&
           data_ < span_.data() + span_.size());

    return data_;
  }

  span_iterator &operator++() noexcept {
    ++data_;
    return *this;
  }

  span_iterator operator++(int) noexcept {
    span_iterator<ElementType, Extent> t = *this;
    ++(*this);
    return t;
  }

  span_iterator &operator--() noexcept {
    --data_;
    return *this;
  }

  span_iterator operator--(int) noexcept {
    span_iterator<ElementType, Extent> t = *this;
    --(*this);
    return t;
  }

  span_iterator &operator+=(difference_type n) noexcept {
    data_ += n;
    return *this;
  }

  span_iterator &operator-=(difference_type n) noexcept {
    data_ -= n;
    return *this;
  }

  span_iterator operator+(difference_type n) const noexcept {
    span_iterator<ElementType, Extent> t = *this;
    return t += n;
  }

  span_iterator operator-(difference_type n) const noexcept {
    span_iterator<ElementType, Extent> t = *this;
    return t -= n;
  }

  friend span_iterator operator+(difference_type n,
                                 const span_iterator &i) noexcept {
    return i + n;
  }

  friend difference_type operator-(const span_iterator &l,
                                   const span_iterator &r) noexcept {
    assert(l.span_.data() == r.span_.data() &&
           l.span_.size() == r.span_.size());

    return l.data_ - r.data_;
  }

  reference operator[](difference_type n) const noexcept {
    return *(*this + n);
  }

  friend bool operator==(const span_iterator &l,
                         const span_iterator &r) noexcept {
    assert(l.span_.data() == r.span_.data() &&
           l.span_.size() == r.span_.size());

    return l.data_ == r.data_;
  }

  friend bool operator!=(const span_iterator &l,
                         const span_iterator &r) noexcept {
    return !(l == r);
  }

  friend bool operator<(const span_iterator &l,
                        const span_iterator &r) noexcept {
    assert(l.span_.data() == r.span_.data() &&
           l.span_.size() == r.span_.size());

    return l.data_ < r.data_;
  }

  friend bool operator>(const span_iterator &l,
                        const span_iterator &r) noexcept {
    return r < l;
  }

  friend bool operator<=(const span_iterator &l,
                         const span_iterator &r) noexcept {
    return !(l > r);
  }

  friend bool operator>=(const span_iterator &l,
                         const span_iterator &r) noexcept {
    return !(l < r);
  }

  operator span_iterator<std::add_const_t<ElementType>, Extent>() const
      noexcept {
    return {data_, span_};
  }

private:
  span_iterator(pointer data, span<std::add_const_t<ElementType>, Extent> span)
      : data_(data), span_(std::move(span)) {}

  pointer data_;
  span<std::add_const_t<ElementType>, Extent> span_;

  friend class span_iterator<std::remove_const_t<ElementType>, Extent>;
  friend class vexocide::span<ElementType, Extent>;
  friend class vexocide::span<std::remove_const_t<ElementType>, Extent>;
};

template <typename T> struct is_span_or_array_impl : std::false_type {};

template <class ElementType, ptrdiff_t Extent>
struct is_span_or_array_impl<span<ElementType, Extent>> : std::true_type {};

template <typename T, std::size_t N>
struct is_span_or_array_impl<std::array<T, N>> : std::true_type {};

template <typename T>
struct is_span_or_array : is_span_or_array_impl<std::remove_cv_t<T>> {};

}

// A view over a contiguous, single-dimension sequence of objects
template <class ElementType, std::ptrdiff_t Extent /* = dynamic_extent */>
class span {
public:
  // constants and types
  using element_type = ElementType;
  using index_type = std::ptrdiff_t;
  using difference_type = std::ptrdiff_t;
  using pointer = std::add_pointer_t<element_type>;
  using reference = std::add_lvalue_reference_t<element_type>;
#ifdef NDEBUG
  using iterator = std::add_pointer_t<element_type>;
  using const_iterator = std::add_pointer_t<std::add_const_t<element_type>>;
#else
  using iterator = detail::span_iterator<ElementType, Extent>;
  using const_iterator =
      detail::span_iterator<std::add_const_t<element_type>, Extent>;
#endif
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  constexpr static index_type extent = Extent;

  // [span.cons], span constructors, copy, assignment, and destructor
  constexpr span() : data_(nullptr), size_(0) {
    static_assert(extent == dynamic_extent || extent == 0,
                  "extent == dynamic_extent || extent == 0");
  }

  constexpr span(std::nullptr_t) : data_(nullptr), size_(0) {
    static_assert(extent == dynamic_extent || extent == 0,
                  "extent == dynamic_extent || extent == 0");
  }

  constexpr span(pointer ptr, index_type count) : data_(ptr), size_(count) {
    assert((ptr == nullptr ? count == 0 : count >= 0) &&
           (extent == dynamic_extent || count == extent));
  }

  // FIXME: ambigious with span<ElementType, Extent>{pointer, 0}
  constexpr span(pointer firstElem, pointer lastElem)
      : data_(firstElem), size_(std::distance(firstElem, lastElem)) {
    assert(std::distance(firstElem, lastElem) >= 0 &&
           (extent == dynamic_extent ||
            std::distance(firstElem, lastElem) == extent));
  }

  template <size_t N>
  constexpr span(element_type (&arr)[N])
      : data_(std::addressof(arr[0])), size_(N) {
    static_assert(extent == dynamic_extent || N == extent,
                  "If extent is not equal to dynamic_extent, then N == extent");
  }

  template <size_t N>
  constexpr span(std::array<element_type, N> &arr)
      : data_(std::addressof(arr[0])), size_(N) {
    static_assert(extent == dynamic_extent || N == extent,
                  "If extent != dynamic_extent && N != extent, then the "
                  "program is ill-formed");
  }

  // FIXME: overloads deviate from P0122R3
  template <size_t N, typename = std::enable_if_t<
                          N == N && std::is_const<element_type>::value>>
  constexpr span(const std::array<std::remove_const_t<element_type>, N> &arr)
      : data_(std::addressof(arr[0])), size_(N) {
    static_assert(extent == dynamic_extent || N == extent,
                  "If extent != dynamic_extent && N != extent, then the "
                  "program is ill-formed");
  }

  template <class Container,
            typename = std::enable_if_t<
                !detail::is_span_or_array<Container>::value &&
                std::is_same<std::remove_reference_t<
                                 decltype(std::declval<Container>()[0])>,
                             std::remove_const_t<element_type>>::value &&
                std::is_same<decltype(std::declval<Container>().size()),
                             typename Container::size_type>::value>>
  constexpr span(Container &cont)
      : data_(std::addressof(cont[0])), size_(cont.size()) {
    assert(extent == dynamic_extent ||
           static_cast<index_type>(cont.size()) == extent);
  }

  template <class Container,
            typename = std::enable_if_t<
                !detail::is_span_or_array<Container>::value &&
                std::is_same<std::remove_reference_t<
                                 decltype(std::declval<Container>()[0])>,
                             std::remove_const_t<element_type>>::value &&
                std::is_same<decltype(std::declval<Container>().size()),
                             typename Container::size_type>::value &&
                std::is_const<element_type>::value>>
  constexpr span(const Container &cont)
      : data_(std::addressof(cont[0])), size_(cont.size()) {
    assert(extent == dynamic_extent ||
           static_cast<index_type>(cont.size()) == extent);
  }

  constexpr span(const span &other) noexcept = default;

  constexpr span(span &&other) noexcept = default;

  template <class OtherElementType, ptrdiff_t OtherExtent,
            typename = std::enable_if<
                std::is_convertible<ElementType, OtherElementType>::value &&
                (Extent == dynamic_extent || OtherExtent == dynamic_extent ||
                 Extent == OtherExtent)>>
  constexpr span(const span<OtherElementType, OtherExtent> &other)
      : data_(reinterpret_cast<pointer>(other.data())), size_(other.size()) {
    assert(extent == dynamic_extent || other.size() == extent);
  }

  template <class OtherElementType, ptrdiff_t OtherExtent,
            typename = std::enable_if<
                std::is_convertible<ElementType, OtherElementType>::value &&
                (Extent == dynamic_extent || OtherExtent == dynamic_extent ||
                 Extent == OtherExtent)>>
  constexpr span(span<OtherElementType, OtherExtent> &&other)
      : data_(reinterpret_cast<pointer>(other.data())), size_(other.size()) {
    assert(extent == dynamic_extent || other.size() == extent);
  }

  ~span() noexcept = default;

  constexpr span &operator=(const span &other) noexcept = default;

  constexpr span &operator=(span &&other) noexcept = default;

  // [span.sub], span subviews
  template <ptrdiff_t Count> constexpr span<element_type, Count> first() const {
    static_assert(Count >= 0, "Count >= 0");
    assert(Count <= size());

    return {data(), Count};
  }

  template <ptrdiff_t Count> constexpr span<element_type, Count> last() const {
    static_assert(Count >= 0, "Count >= 0");
    assert(Count <= size());

    return {data() + (size() - Count), Count};
  }

  template <ptrdiff_t Offset, ptrdiff_t Count = dynamic_extent>
  constexpr span<element_type, Count> subspan() const {
    static_assert(Offset >= 0 && (Count == dynamic_extent || Count >= 0),
                  "Offset >= 0 && (Count == dynamic_extent || Count >= 0)");

    // FIXME: Offset < size() per P0122R3
    assert(Offset <= size() &&
           (Count == dynamic_extent || Offset + Count <= size()));

    return {data() + Offset, Count == dynamic_extent ? size() - Offset : Count};
  }

  constexpr span<element_type, dynamic_extent> first(index_type count) const {
    assert(count >= 0 && count <= size());

    return {data(), count};
  }

  constexpr span<element_type, dynamic_extent> last(index_type count) const {
    assert(count >= 0 && count <= size());

    return {data() + (size() - count), count};
  }

  constexpr span<element_type, dynamic_extent>
  subspan(index_type offset, index_type count = dynamic_extent) const {
    // FIXME: offset < size() per P0122R3
    assert(offset >= 0 && offset <= size() &&
           (count == dynamic_extent || count >= 0) && offset + count <= size());

    return {data() + offset, count == dynamic_extent ? size() - offset : count};
  }

  // [span.obs], span observers
  constexpr index_type length() const noexcept { return size(); }

  constexpr index_type size() const noexcept { return size_; }

  constexpr index_type length_bytes() const noexcept { return size_bytes(); }

  constexpr index_type size_bytes() const noexcept {
    return size() * sizeof(element_type);
  }

  constexpr bool empty() const noexcept { return size() == 0; }

  // [span.elem], span element access
  constexpr reference operator[](index_type idx) const {
    assert(idx >= 0 && idx < size());

    return *(data() + idx);
  }

  constexpr reference operator()(index_type idx) const {
    assert(idx >= 0 && idx < size());

    return *(data() + idx);
  }

  constexpr pointer data() const noexcept { return data_; }

  // [span.iter], span iterator support
  iterator begin() const noexcept {
#ifdef NDEBUG
    return data();
#else
    return {data(), *this};
#endif
  }

  iterator end() const noexcept {
#ifdef NDEBUG
    return data() + size();
#else
    return {data() + size(), *this};
#endif
  }

  const_iterator cbegin() const noexcept {
#ifdef NDEBUG
    return data();
#else
    return {data(), *this};
#endif
  }

  const_iterator cend() const noexcept {
#ifdef NDEBUG
    return data() + size();
#else
    return {data() + size(), *this};
#endif
  }

  reverse_iterator rbegin() const noexcept { return reverse_iterator{end()}; }

  reverse_iterator rend() const noexcept { return reverse_iterator{begin()}; }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator{cend()};
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator{cbegin()};
  }

private:
  pointer data_;    // exposition only
  index_type size_; // exposition only
};

// [span.comparison], span comparison operators
template <class ElementType, ptrdiff_t Extent>
constexpr bool operator==(const span<ElementType, Extent> &l,
                          const span<ElementType, Extent> &r) noexcept {
  return std::equal(l.begin(), l.end(), r.begin(), r.end());
}

template <class ElementType, ptrdiff_t Extent>
constexpr bool operator!=(const span<ElementType, Extent> &l,
                          const span<ElementType, Extent> &r) noexcept {
  return !(l == r);
}

template <class ElementType, ptrdiff_t Extent>
constexpr bool operator<(const span<ElementType, Extent> &l,
                         const span<ElementType, Extent> &r) noexcept {
  return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}

template <class ElementType, ptrdiff_t Extent>
constexpr bool operator<=(const span<ElementType, Extent> &l,
                          const span<ElementType, Extent> &r) noexcept {
  return !(l > r);
}

template <class ElementType, ptrdiff_t Extent>
constexpr bool operator>(const span<ElementType, Extent> &l,
                         const span<ElementType, Extent> &r) noexcept {
  return r < l;
}

template <class ElementType, ptrdiff_t Extent>
constexpr bool operator>=(const span<ElementType, Extent> &l,
                          const span<ElementType, Extent> &r) noexcept {
  return !(l < r);
}

// [span.objectrep], views of object representation
template <class ElementType, ptrdiff_t Extent>
span<const byte,
     ((Extent == dynamic_extent)
          ? dynamic_extent
          : static_cast<std::ptrdiff_t>(sizeof(ElementType) * Extent))>
as_bytes(span<ElementType, Extent> s) noexcept {
  return {reinterpret_cast<const byte *>(s.data()),
          static_cast<std::ptrdiff_t>(sizeof(ElementType) * s.size())};
}

template <class ElementType, ptrdiff_t Extent,
          typename = std::enable_if_t<!std::is_const<
              typename span<ElementType, Extent>::element_type>::value>>
span<byte, ((Extent == dynamic_extent)
                ? dynamic_extent
                : static_cast<std::ptrdiff_t>(sizeof(ElementType) * Extent))>
as_writeable_bytes(span<ElementType, Extent> s) noexcept {
  return {reinterpret_cast<byte *>(s.data()),
          static_cast<std::ptrdiff_t>(sizeof(ElementType) * s.size())};
}

}

#endif
