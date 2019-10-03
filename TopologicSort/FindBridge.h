#pragma once

#include "Graph.h"

void dfs( Graph5& graph, size_t v, size_t parent, size_t& time, IArray< size_t >& fup, IArray< bool >& used, IArray< size_t >& tin, IArray< std::pair< size_t, size_t > >& bridge )
{
    used[v] = true;
    time++;
    fup[v] = tin[v] = time;
    for( size_t i = 0; i < graph[v].size(); ++i )
    {
        auto u = graph[v][i].v;
        if( parent != u )
        {
            if( used[u] )
            {
                fup[v] = ( std::min )( fup[v], tin[u] );
            }
            else
            {
                dfs( graph, u, v, time, fup, used, tin, bridge );
                fup[v] = ( std::min )( fup[v], fup[u] );
                if( fup[u] > tin[v] )
                {
                    bridge.add( std::make_pair( v, u ) );
                }
            }
        }
    }
}

template< class Ty >
pIArray< Ty > create( size_t size, const Ty& defaultValue )
{
    pIArray< Ty > cont{ new VectorArray< Ty >( size ) };
    for( size_t i = 0; i < size; ++i )
        cont->add( defaultValue );
    return cont;
}

pIArray< std::pair< size_t, size_t > > FindBridge( Graph5& graph )
{
    pIArray< size_t > tin = create( graph.size(), size_t(0) );
    pIArray< bool > used = create( graph.size(), false );
    pIArray< size_t > fup = create( graph.size(), size_t( 0 ) );

    pIArray< std::pair< size_t, size_t > > bridge( new FactorArray< std::pair< size_t, size_t > > );

    for( size_t i = 0; i < used->size(); ++i )
    {
        if( (*used)[i] == false )
        {
            size_t time = 0;
            dfs( graph, i, -1, time, *fup, *used, *tin, *bridge );
        }
    }

    return bridge;
}
