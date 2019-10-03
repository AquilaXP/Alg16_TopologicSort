#pragma once

#include "Graph.h"

enum
{
    GREY,
    WHITE,
    BLACK
};

/// Функция взята из 15 урока, подоходит почти полностью!(заменил IArray на Stack)
void visit( Graph5& graph, size_t num, IArray<size_t>& color, Stack< size_t >& res )
{
    Stack< size_t > stack;
    stack.push( num );
    color[num] = GREY;
    std::vector< size_t > processed( graph.size(), 0 );
    while( stack.isEmpty() == false )
    {
        size_t i = stack.pop();
        stack.push( i );
        if( processed[i] == graph[i].size() )
        {
            color[i] = BLACK;
            res.push( stack.pop() );
        }
        else
        {
            size_t j;
            for( j = processed[i]; j < graph[i].size(); ++j )
            {
                const auto& node = graph[i][j];
                if( color[node.v] == WHITE )
                {
                    stack.push( node.v );
                    color[node.v] = GREY;
                    ++j;
                    break;
                }
            }
            processed[i] = j;
        }
    }
}

void Taryana( Graph5& graph, IArray< size_t >& arr )
{
    VectorArray< size_t > color( graph.size() );
    for( size_t i = 0; i < graph.size(); ++i )
        color.add( WHITE );

    Stack< size_t > stack;
    for( size_t i = 0; i < color.size(); ++i )
    {
        if( color[i] == WHITE )
        {
            visit( graph, i, color, stack );
        }
    }

    arr.clear();
    while( stack.isEmpty() == false )
        arr.add( stack.pop() );
}
