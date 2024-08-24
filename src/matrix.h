#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <cstddef>
#include <unordered_map>
#include <array>
#include <utility>
#include <type_traits>
#include <optional>
#include <functional>

namespace homework_6
{

#define UNUSED(variable) (void)variable

template <typename T,
          std::size_t dimensions,
          typename Allocator = std::allocator<T>>
class Matrix
{
public:
    friend Matrix<T, dimensions + 1, Allocator>;
	
    using ValueType     = T;
    using MatrixType    = Matrix<T, dimensions, Allocator>;
    using SubMatrixType = Matrix<T, dimensions - 1, Allocator>;
    using IndexType     = std::array<std::size_t, dimensions>;
    using SubIndexType  = std::array<std::size_t, dimensions - 1>;

private:
    using KeyValueType  = std::pair<const std::size_t, SubMatrixType>;
    using StorageType   = std::unordered_map<std::size_t,
                                             SubMatrixType,
                                             std::hash<std::size_t>,
                                             std::equal_to<std::size_t>,
                                             typename std::allocator_traits<Allocator>::template rebind_alloc<KeyValueType>
                                            >;

public:
    explicit Matrix(T default_value);

    Matrix() = default;

    Matrix(const Matrix&) = default;
    Matrix& operator=(const Matrix&) = default;
    Matrix(Matrix&&) noexcept = default;
    Matrix& operator=(Matrix&&) noexcept = default;

    [[nodiscard]] std::size_t size() const;

    [[nodiscard]] bool empty() const;

    void shrink_to_fit();

    [[nodiscard]] SubMatrixType& operator[](std::size_t index);
    [[nodiscard]] const SubMatrixType& operator[](std::size_t index) const;

    [[nodiscard]] T& at(const IndexType& index);
    [[nodiscard]] const T& at(const IndexType& index) const;

private:
    template <typename IndexIterator>
    T& at(IndexIterator begin, IndexIterator end);
    template <typename IndexIterator>
    const T& at(IndexIterator begin, IndexIterator end) const;

private:
    template <bool Const>
    class IteratorT
    {
    private:
        enum class Type { BEGIN, END, };
        friend MatrixType;
        using InstancePtr    = std::conditional_t<Const, const MatrixType*, MatrixType*>;
        using ValueReference = std::conditional_t<Const, const T&, T&>;
        IteratorT(InstancePtr instance, Type type);

    public:

        [[nodiscard]] std::pair<IndexType, ValueReference> operator*() const;

        [[nodiscard]] IndexType index() const;

        [[nodiscard]] ValueReference value() const;

        IteratorT& operator++();

        [[nodiscard]] const IteratorT operator++(int);

        [[nodiscard]] bool operator==(const IteratorT& other) const;
        [[nodiscard]] bool operator!=(const IteratorT& other) const;

    private:
        InstancePtr m_instance;
        std::optional<typename SubMatrixType::template IteratorT<Const>> m_sub_iterator;
        using StorageIterator = std::conditional_t<Const, typename StorageType::const_iterator, typename StorageType::iterator>;
        StorageIterator m_current_iterator;
    };

public:
    using Iterator      = IteratorT<false>;
    using ConstIterator = IteratorT<true>;

    [[nodiscard]] Iterator begin();

    [[nodiscard]] Iterator end();

    [[nodiscard]] ConstIterator begin() const;

    [[nodiscard]] ConstIterator end() const;

private:
    StorageType m_values;
    T m_default_value{};
};


template <typename T,
          typename Allocator>
class Matrix<T, 0, Allocator>
{
public:
    friend Matrix<T, 1, Allocator>;

    using ValueType  = T;
    using MatrixType = Matrix<T, 0, Allocator>;
    using IndexType  = std::array<std::size_t, 0>;

    explicit Matrix(const T& default_value);

    Matrix() = default;
    Matrix(const Matrix&) = default;
    Matrix& operator=(const Matrix&) = default;
    Matrix(Matrix&&) noexcept = default;
    Matrix& operator=(Matrix&&) noexcept = default;

    Matrix& operator=(const T& value);

    Matrix& operator=(T&& value);

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool empty() const;

    operator T&();

    operator const T&() const;

    [[nodiscard]] T& at(const IndexType&);
    [[nodiscard]] const T& at(const IndexType&) const;

private:
    template <typename IndexIterator>
    T& at(IndexIterator, IndexIterator);
    template <typename IndexIterator>
    const T& at(IndexIterator, IndexIterator) const;

private:
    template <bool Const>
    class IteratorT
    {
    private:
        enum class Type { BEGIN, END, };
        friend MatrixType;
        using InstancePtr    = std::conditional_t<Const, const MatrixType*, MatrixType*>;
        using ValueReference = std::conditional_t<Const, const T&, T&>;
        IteratorT(InstancePtr instance, Type type);

    public:
        [[nodiscard]] std::pair<IndexType, ValueReference> operator*() const;
        [[nodiscard]] IndexType index() const;
        [[nodiscard]] ValueReference value() const;

        IteratorT& operator++();
        [[nodiscard]] const IteratorT operator++(int);

        [[nodiscard]] bool operator==(const IteratorT& other) const;
        [[nodiscard]] bool operator!=(const IteratorT& other) const;

    private:
        InstancePtr m_instance;
        Type m_type;
    };

public:
    using Iterator      = IteratorT<false>;
    using ConstIterator = IteratorT<true>;

    [[nodiscard]] Iterator begin();
    [[nodiscard]] Iterator end();
    [[nodiscard]] ConstIterator begin() const;
    [[nodiscard]] ConstIterator end() const;

private:
    T m_value{};
    T m_default_value{};
};

#define TEMPLATE_ARGS       template <typename T, std::size_t dimensions, typename Allocator>
#define MATRIX_TYPE         Matrix<T, dimensions, Allocator>

TEMPLATE_ARGS
MATRIX_TYPE::Matrix(T default_value)
    : m_default_value(std::move(default_value))
{
}

TEMPLATE_ARGS
std::size_t MATRIX_TYPE::size() const
{
    std::size_t answer = 0;
    for (const auto& [index, value] : m_values)
    {
        answer += value.size();
        UNUSED(index);
    }
    return answer;
}

TEMPLATE_ARGS
bool MATRIX_TYPE::empty() const
{
    return size() == 0;
}


TEMPLATE_ARGS
void MATRIX_TYPE::shrink_to_fit()
{
    for (auto it = m_values.begin(); it != m_values.end();)
    {
        if (it->second.empty())
            it = m_values.erase(it);
        else
            ++it;
    }
}


TEMPLATE_ARGS
typename MATRIX_TYPE::SubMatrixType& MATRIX_TYPE::operator[](std::size_t index)
{
    auto it = m_values.find(index);
    if (it != m_values.end())
        return it->second;
    auto [emplaced, b] = m_values.emplace(index, Matrix<T, dimensions - 1, Allocator>(m_default_value));
    UNUSED(b);
    return emplaced->second;
}

TEMPLATE_ARGS
const typename MATRIX_TYPE::SubMatrixType& MATRIX_TYPE::operator[](std::size_t index) const
{
    auto it = m_values.find(index);
    if (it != m_values.end())
        return it->second;
    auto [emplaced, _] = m_values.emplace(index, Matrix<T, dimensions - 1, Allocator>(m_default_value));
    return emplaced->second;
}

TEMPLATE_ARGS
T& MATRIX_TYPE::at(const IndexType& index)
{
    return operator[](index[0]).at(index.data() + 1, index.data() + index.size());
}

TEMPLATE_ARGS
const T& MATRIX_TYPE::at(const IndexType& index) const
{
    return operator[](index[0]).at(index.data() + 1, index.data() + index.size());
}

TEMPLATE_ARGS
template <typename IndexIterator>
T& MATRIX_TYPE::at(IndexIterator begin, IndexIterator end)
{
    return operator[](*begin).at(std::next(begin), end);
}


TEMPLATE_ARGS
template <typename IndexIterator>
const T& MATRIX_TYPE::at(IndexIterator begin, IndexIterator end) const
{
    return operator[](*begin).at(std::next(begin), end);
}

TEMPLATE_ARGS
typename MATRIX_TYPE::ConstIterator MATRIX_TYPE::begin() const
{
    return ConstIterator(this, ConstIterator::Type::BEGIN);
}

TEMPLATE_ARGS
typename MATRIX_TYPE::ConstIterator MATRIX_TYPE::end() const
{
    return ConstIterator(this, ConstIterator::Type::END);
}


TEMPLATE_ARGS
typename MATRIX_TYPE::Iterator MATRIX_TYPE::begin()
{
    return Iterator(this, Iterator::Type::BEGIN);
}

TEMPLATE_ARGS
typename MATRIX_TYPE::Iterator MATRIX_TYPE::end()
{
    return Iterator(this, Iterator::Type::END);
}


#define ITERATOR    MATRIX_TYPE::IteratorT<Const>
#define ITERATOR_T  MATRIX_TYPE::template IteratorT<Const>

TEMPLATE_ARGS
template <bool Const>
ITERATOR_T::IteratorT(InstancePtr instance, Type type)
    : m_instance(instance)
{
    switch (type)
    {
    case Type::BEGIN:
    {
        m_current_iterator = m_instance->m_values.begin();
        bool init = false;
        for (; m_current_iterator != m_instance->m_values.end(); ++m_current_iterator)
        {
            for (m_sub_iterator  = m_current_iterator->second.begin();
                 m_sub_iterator != m_current_iterator->second.end();
                 ++m_sub_iterator.value())
            {
                if (m_sub_iterator.value().value() != m_instance->m_default_value)
                {
                    init = true;
                    goto after_loop;
                }
            }
        }
        after_loop: ;

        if (!init)
            m_sub_iterator = std::nullopt;

        break;
    }
    case Type::END:
        m_current_iterator = m_instance->m_values.end();
        m_sub_iterator = std::nullopt;
        break;
    }
}

TEMPLATE_ARGS
template <bool Const>
std::pair<typename MATRIX_TYPE::IndexType, typename ITERATOR_T::ValueReference> ITERATOR::operator*() const
{
    std::pair<IndexType, ValueReference> p(index(), value());
    return p;
}

TEMPLATE_ARGS
template <bool Const>
typename MATRIX_TYPE::IndexType ITERATOR::index() const
{
    IndexType answer;
    answer[0] = m_current_iterator->first;
    SubIndexType subindex = m_sub_iterator.value().index();
    for (std::size_t i = 0; i < subindex.size(); ++i)
        answer[i + 1] = subindex[i];
    return answer;
}

TEMPLATE_ARGS
template <bool Const>
typename ITERATOR_T::ValueReference ITERATOR::value() const
{
    ValueReference ans = m_sub_iterator.value().value();
    return ans;
}

TEMPLATE_ARGS
template <bool Const>
typename ITERATOR_T& ITERATOR::operator++()
{
    auto job = [this]() -> void
    {
        ++m_sub_iterator.value();
        while (m_sub_iterator == m_current_iterator->second.end())
        {
            ++m_current_iterator;
            if (m_current_iterator == m_instance->m_values.end())
            {
                m_sub_iterator = std::nullopt;
                return;
            }
            m_sub_iterator = m_current_iterator->second.begin();
        }
    };

    do
    {
        job();
    } while (m_sub_iterator != std::nullopt && value() == m_instance->m_default_value);

    return *this;
}

TEMPLATE_ARGS
template <bool Const>
const typename ITERATOR_T ITERATOR::operator++(int)
{
    IteratorT<Const> old = *this;
    ++(*this);
    return old;
}

TEMPLATE_ARGS
template <bool Const>
bool ITERATOR::operator==(const ITERATOR& other) const
{
    return std::tie(m_instance, m_sub_iterator, m_current_iterator) ==
           std::tie(other.m_instance, other.m_sub_iterator, other.m_current_iterator);
}

TEMPLATE_ARGS
template <bool Const>
bool ITERATOR::operator!=(const ITERATOR& other) const
{
    return !(*this == other);
}

#undef ITERATOR
#undef ITERATOR_T

#undef TEMPLATE_ARGS
#undef MATRIX_TYPE

#define TEMPLATE_ARGS_0D    template <typename T, typename Allocator>
#define MATRIX_TYPE_0D      Matrix<T, 0, Allocator>

TEMPLATE_ARGS_0D
MATRIX_TYPE_0D::Matrix(const T& default_value)
    : m_value(default_value)
    , m_default_value(default_value)
{
}

TEMPLATE_ARGS_0D
MATRIX_TYPE_0D& MATRIX_TYPE_0D::operator=(const T& value)
{
    m_value = value;
    return *this;
}

TEMPLATE_ARGS_0D
MATRIX_TYPE_0D& MATRIX_TYPE_0D::operator=(T&& value)
{
    m_value = std::move(value);
    return *this;
}

TEMPLATE_ARGS_0D
std::size_t MATRIX_TYPE_0D::size() const
{
    return (m_value == m_default_value ? 0 : 1);
}

TEMPLATE_ARGS_0D
bool MATRIX_TYPE_0D::empty() const
{
    return size() == 0;
}

TEMPLATE_ARGS_0D
MATRIX_TYPE_0D::operator const T&() const
{
    return m_value;
}

TEMPLATE_ARGS_0D
MATRIX_TYPE_0D::operator T&()
{
    return m_value;
}

TEMPLATE_ARGS_0D
T& MATRIX_TYPE_0D::at(const IndexType&)
{
    return m_value;
}

TEMPLATE_ARGS_0D
template <typename IndexIterator>
T& MATRIX_TYPE_0D::at(IndexIterator, IndexIterator)
{
    return m_value;
}


TEMPLATE_ARGS_0D
typename MATRIX_TYPE_0D::ConstIterator MATRIX_TYPE_0D::begin() const
{
    return ConstIterator(this, ConstIterator::Type::BEGIN);
}

TEMPLATE_ARGS_0D
typename MATRIX_TYPE_0D::ConstIterator MATRIX_TYPE_0D::end() const
{
    return ConstIterator(this, ConstIterator::Type::END);
}

TEMPLATE_ARGS_0D
typename MATRIX_TYPE_0D::Iterator MATRIX_TYPE_0D::begin()
{
    return Iterator(this, Iterator::Type::BEGIN);
}

TEMPLATE_ARGS_0D
typename MATRIX_TYPE_0D::Iterator MATRIX_TYPE_0D::end()
{
    return Iterator(this, Iterator::Type::END);
}


#define ITERATOR_0D      MATRIX_TYPE_0D::IteratorT<Const>
#define ITERATOR_0D_T    MATRIX_TYPE_0D::template IteratorT<Const>

TEMPLATE_ARGS_0D
template <bool Const>
ITERATOR_0D::IteratorT(InstancePtr instance, Type type)
    : m_instance(instance)
    , m_type(type)
{
}

TEMPLATE_ARGS_0D
template <bool Const>
std::pair<typename MATRIX_TYPE_0D::IndexType, typename ITERATOR_0D_T::ValueReference> ITERATOR_0D::operator*() const
{
    std::pair<IndexType, ValueReference> p(index(), value());
    return p;
}

TEMPLATE_ARGS_0D
template <bool Const>
typename MATRIX_TYPE_0D::IndexType ITERATOR_0D::index() const
{
    return {};
}

TEMPLATE_ARGS_0D
template <bool Const>
typename ITERATOR_0D_T::ValueReference ITERATOR_0D::value() const
{
    return m_instance->m_value;
}

TEMPLATE_ARGS_0D
template <bool Const>
typename ITERATOR_0D_T& ITERATOR_0D::operator++()
{
    m_type = Type::END;
    return *this;
}

TEMPLATE_ARGS_0D
template <bool Const>
const typename ITERATOR_0D_T ITERATOR_0D::operator++(int)
{
    IteratorT<Const> old = *this;
    ++(*this);
    return old;
}

TEMPLATE_ARGS_0D
template <bool Const>
bool ITERATOR_0D::operator==(const ITERATOR_0D& other) const
{
    return std::tie(m_instance, m_type) == std::tie(other.m_instance, other.m_type);
}

TEMPLATE_ARGS_0D
template <bool Const>
bool ITERATOR_0D::operator!=(const ITERATOR_0D& other) const
{
    return !(*this == other);
}

#undef ITERATOR_0D
#undef ITERATOR_0D_T

#undef TEMPLATE_ARGS_0D
#undef MATRIX_TYPE_0D

#undef UNUSED

} // namespace homework_6

#endif // MATRIX_H
