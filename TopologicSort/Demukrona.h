#pragma once

#include <iomanip>

#include "Graph.h"

bool Demukrona( Graph5& graph, IArray< psIArray< size_t > >& res )
{
    VectorArray< size_t > A( graph.size() );

    for( size_t i = 0; i < graph.size(); ++i )
        A.add( 0 );

    // Считаем полустепень захода
    for( size_t i = 0; i < graph.size(); ++i )
    {
        for( size_t j = 0; j < graph[i].size(); ++j )
        {
            A[graph[i][j].v] += 1;
        }
    }
    res.clear();
    res.add( std::make_shared<FactorArray< size_t > >() );

    size_t unproccedNode = A.size();
    // Работаем пока не обработаем все вершины
    while( unproccedNode != 0 )
    {
        /// Если уровень хоть чем-то заполнен, то подготавливаем следующий
        if( res[res.size() - 1]->size() > 0 )
            res.add( std::make_shared<FactorArray< size_t > >() );

        auto& lastLayer = *(res[res.size()-1]);
        for( size_t i = 0; i < A.size(); ++i )
        {
            if( A[i] == 0 )
            {
                --unproccedNode;
                lastLayer.add( i );
                A[i] = size_t( -1 );
            }
        }
        // Невозможно!
        if( lastLayer.size() == 0 )
            return false;

        // Удаляем вершины из слоя
        for( size_t i = 0; i < lastLayer.size(); ++i )
        {
            size_t curr = lastLayer[ i ];
            for( size_t j = 0; j < graph[curr].size(); ++j )
            {
                A[graph[curr][j].v] -= 1;
            }
        }
    }

    return true;
}