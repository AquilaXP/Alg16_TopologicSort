#pragma once

#include <memory>

#include "Array/IArray.h"
#include "Array/FactorArray.h"
#include "Array/VectorArray.h"
#include "Array/Stack.h"

/// ������ ������� ���� � ��� �����
struct NodeGraph
{
    NodeGraph() = default;
    NodeGraph( size_t v, int32_t w = 1 )
        : v( v ), w( w )
    {}

    size_t v = 0;
    int32_t w = 0;
};

/// ��������������� ����� ��� ������ �� ������� ������� ���������
/// �� ��������� ����� ������� Node ��� ������� node.
/// ������� ���� ����������� � ������ ���������� �� ���� �����. ��������� �� ��������
struct ProxyArray
{
    ProxyArray( NodeGraph* ptr, size_t& size )
        : m_p( ptr ), m_size( size )
    {
    }

    void add( const NodeGraph& val )
    {
        /// ���� ���� ��������
        auto it = std::lower_bound( &m_p[0], &m_p[m_size], val,
            []( const NodeGraph& it, const NodeGraph& val )
        {
            return it.w < val.w;
        } );

        size_t i = it - &m_p[0];
        // �������
        for( size_t j = m_size; j != i; --j )
        {
            m_p[j] = m_p[j - 1];
        }
        // ��������� �� ������ �����
        m_p[i] = val;
        ++m_size;
    }

    void clear()
    {
        m_size = 0;
    }
    NodeGraph* begin()
    {
        return m_p;
    }
    NodeGraph* end()
    {
        return m_p + m_size;
    }
    NodeGraph& operator [] ( size_t idx )
    {
        return m_p[idx];
    }
    size_t size() const noexcept
    {
        return m_size;
    }

private:
    NodeGraph* m_p = nullptr;
    size_t& m_size;
};

/// ���� - ������ ��������� � ������ �����
struct Graph5
{
    Graph5( size_t n, size_t maxS ) : m_data( n * maxS ), m_sizes( n ), m_maxS( maxS )
    {
        m_N = n;

        for( size_t i = 0; i < n * maxS; ++i )
        {
            m_data.add( { 0, 0 } );
        }
        for( size_t i = 0; i < n; ++i )
        {
            m_sizes.add( 0 );
        }
    }
    void clear()
    {
        m_N = 0;
        m_maxS = 0;
        m_data.clear();
        m_sizes.clear();
    }
    size_t size() const
    {
        return m_N;
    }
    size_t maxS() const
    {
        return m_maxS;
    }
    ProxyArray operator [] ( size_t indexV )
    {
        return ProxyArray( &m_data.get(indexV * m_maxS), m_sizes.get( indexV ) );
    }
private:
    size_t m_N = 0;
    size_t m_maxS = 0;
    VectorArray< size_t > m_sizes;
    VectorArray< NodeGraph > m_data;
};

/// ��������� �����.
Graph5 reverse( Graph5& src )
{
    Graph5 dst( src.size(), src.maxS() );

    for( size_t i = 0; i < src.size(); ++i )
    {
        auto p = src[i];
        for( size_t j = 0; j < p.size(); ++j )
        {
            NodeGraph n = p[j];
            dst[n.v].add( { i, n.w } );
        }
    }

    return dst;
}
