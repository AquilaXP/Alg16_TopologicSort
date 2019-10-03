#include <iostream>

#include "Demukrona.h"
#include "Taryana.h"
#include "FindBridge.h"

void TestTayana()
{
    /// Для тестирования, использовал вариант из урока
    Graph5 graph( 4, 2 );
    graph[0].add( { 3 } );
    graph[2].add( { 1 } );
    graph[3].add( { 1 } );
    graph[3].add( { 2 } );

    /// Ожидамемый результат
    VectorArray<size_t> etalon( 4 );
    etalon.add( 0 );
    etalon.add( 3 );
    etalon.add( 2 );
    etalon.add( 1 );


    VectorArray< size_t > res;
    Taryana( graph, res );

    if( (res != etalon) )
        throw std::runtime_error( "incorect working algorithm Taryana!" );
}

void print( IArray< psIArray< size_t > >& arr )
{
    for( size_t i = 0; i < arr.size(); ++i )
    {
        std::cout << std::setw( 2 ) << i << ':';
        for( size_t j = 0; j < arr[i]->size(); ++j )
        {
            std::cout << arr[i]->get( j ) << ' ';
        }
        std::cout << '\n';
    }
}

void TestDemukrona()
{
    VectorArray< psIArray< size_t > > etalon( 6 );
    for( size_t i = 0; i < 6; ++i )
        etalon.add( std::make_shared<FactorArray< size_t > >() );

    Graph5 graph( 14, 5 );

    /// Используем рисунок из урока для проверки
    // N0
    etalon[0]->add( 4 );
    graph[4].add( { 2 } );
    graph[4].add( { 8 } );
    graph[4].add( { 9 } );

    etalon[0]->add( 7 );
    graph[7].add( { 1 } );
    graph[7].add( { 3 } );
    graph[7].add( { 5 } );
    graph[7].add( { 13 } );

    // N1
    etalon[1]->add( 1 );
    graph[1].add( { 12 } );

    etalon[1]->add( 8 );
    graph[8].add( { 0 } );
    graph[8].add( { 6 } );

    etalon[1]->add( 9 );
    graph[9].add( { 0 } );
    graph[9].add( { 11 } );
    graph[9].add( { 13 } );
    
    // N2
    etalon[2]->add( 0 );
    graph[0].add( { 2 } );
    graph[0].add( { 12 } );

    etalon[2]->add( 6 );
    graph[6].add( { 5 } );

    etalon[2]->add( 13 );
    graph[13].add( { 10 } );

    // N3
    etalon[3]->add( 5 );
    graph[5].add( { 3 } );
    graph[5].add( { 10 } );
    graph[5].add( { 11 } );
    graph[5].add( { 12 } );

    // N4
    etalon[4]->add( 3 );
    graph[3].add( { 2 } );

    etalon[4]->add( 10 );
    graph[10].add( { 2 } );

    etalon[4]->add( 11 );

    etalon[4]->add( 12 );
    graph[12].add( { 2 } );

    // N5
    etalon[5]->add( 2 );


    VectorArray< psIArray< size_t > > res( 6 );
    bool ret = Demukrona( graph, res );
    if( ret == false )
        throw std::runtime_error( "incorect algorithm Demukrona!" );

    if( res != etalon )
        throw std::runtime_error( "incorect algorithm Demukrona!" );

    // Подпортим граф, зациклим начальные вершины 4 и 7 c 2, чтобы выдала false
    graph[2].add( 4 );
    graph[2].add( 7 );
    res.clear();
    ret = Demukrona( graph, res );
    if( ret == true )
        throw std::runtime_error( "incorect algorithm Demukrona!" );
}

void TestFindBridge()
{
    /// Взят из урока
    Graph5 graph( 10, 4 );

    graph[0].add( 1 );
    graph[0].add( 2 );

    graph[1].add( 2 );

    graph[2].add( 0 );
    graph[2].add( 3 );

    graph[3].add( 4 );
    graph[3].add( 5 );
    graph[3].add( 6 );
    graph[3].add( 7 );

    graph[4].add( 5 );

    graph[5].add( 3 );
    graph[5].add( 9 );

    graph[6].add( 7 );

    graph[7].add( 3 );
    graph[7].add( 8 );

    VectorArray< std::pair< size_t, size_t > > etalon( 3 );
    etalon.add( std::make_pair( 0, 1 ) );
    etalon.add( std::make_pair( 5, 9 ) );
    etalon.add( std::make_pair( 7, 8 ) );

    auto res = FindBridge( graph );

    for( size_t i = 0; i < etalon.size(); ++i )
    {
        bool finded = false;
        for( size_t j = 0; j < res->size(); ++j )
        {
            if( etalon[i] == ( *res )[j] )
            {
                finded = true;
                break;
            }
        }
        if( finded == false )
            throw std::runtime_error( "incorect work algorithm FindBridge!" );
    }

    // Сделаем граф без мостов (треугольник)
    Graph5 graph2( 3, 2 );
    graph2[0].add( 1 );
    graph2[0].add( 2 );

    graph2[1].add( 0 );
    graph2[1].add( 2 );

    graph2[2].add( 0 );
    graph2[2].add( 1 );

    res = FindBridge( graph2 );
    if( res->size() > 0 )
        throw std::runtime_error( "incorect work algorithm FindBridge!" );
}

int main()
{
    try
    {
        TestFindBridge();
        TestDemukrona();
        TestTayana();
    }
    catch( const std::exception& e )
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
