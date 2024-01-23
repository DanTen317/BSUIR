#include <iostream>

#include <sc-memory/sc_memory.hpp>

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>

#include "LargeModularAgent.hpp"

using namespace std;
using namespace utils;

namespace exampleModule {
    SC_AGENT_IMPLEMENTATION(LargeModularAgent)
            {
                    //SC_LOG_DEBUG("Large modular agent. Started");

                    ScAddr actionNode = otherAddr;
            ScAddrVector Input;

            ScIterator3Ptr it3 = m_memoryCtx.Iterator3(
            actionNode,
            ScType::EdgeAccessConstPosPerm,
            ScType::NodeConst);

            while ( it3->Next()){
                Input.push_back(it3->Get(2));                       //добавляем наш объект
                SC_LOG_INFO(m_memoryCtx.HelperGetSystemIdtf(it3->Get(2)));
            }
            ScAddrVector newEdges;                                      //выходной вектор
            createResponseConstruction(newEdges, Input[0], Input[1]);   //генерируем вывод

            SC_LOG_ERROR("Create Response end. Message from main");

            utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, newEdges, true);
            SC_LOG_ERROR("Agent work end");
            return SC_RESULT_OK;
            }

    //Функция для создания выходного графа
    void LargeModularAgent::createResponseConstruction
            (ScAddrVector &newEdges, ScAddr const &graph1, ScAddr const &graph2) {
        vector <FinalNodes> newNodes;

        processing(newNodes, graph1, graph2);

        detectEdges(newNodes, newEdges, graph1, graph2);
    }

    void LargeModularAgent::detectEdges(vector <FinalNodes> &newNodes,
                                         ScAddrVector &newEdges,
                                         ScAddr const &graph1,
                                         ScAddr const &graph2) {
        int counter = 0;
        for (int i = 0; i < newNodes.size(); i++) {
            SC_LOG_ERROR("smth2");
            for (int j = i + 1; j < newNodes.size(); j++) {
                SC_LOG_ERROR("smth3");

                if ((newNodes[i].firstColor != newNodes[j].firstColor) && (newNodes[i].secondColor != newNodes[j].secondColor))
                {
                    counter = 0;

                    ScIterator5Ptr it5_1 = m_memoryCtx.Iterator5(   // итератор для нахождения ребра между first color в первом графе (из xi в xj)
                        newNodes[i].firstColor,
                        ScType::EdgeUCommonConst,
                        newNodes[j].firstColor,
                        ScType::EdgeAccessConstPosPerm,
                        graph1);
                    SC_LOG_ERROR("smth4_1");
                    while (it5_1->Next())
                    {
                        SC_LOG_ERROR("1!!!!!!!");
                        //addResultEdges(newNodes, newEdges, graph2, graph1, i, j);
                        counter++;
                    }
                    
                    
                    ScIterator5Ptr it5_2 = m_memoryCtx.Iterator5(   // обратный от верхнего, просто повторение, для неориентированного графа (из xj в xi)
                        newNodes[j].firstColor,
                        ScType::EdgeUCommonConst,
                        newNodes[i].firstColor,
                        ScType::EdgeAccessConstPosPerm,
                        graph1);
                    SC_LOG_ERROR("smth4_2");
                    while (it5_2->Next())
                    {
                        SC_LOG_ERROR("2!!!!!!!");
                        //addResultEdges(newNodes, newEdges, graph2, graph1, i, j);
                        counter++;
                    }
                

                    // 2 итератора выше для нахождения того, соединены ли первые числа вершин в первом графе
                    
                    // --------------------------------------------------------------------------------------------------------
                    
                    // 2 итератора ниже для нахождения того, соединены ли вторые числа вершин во втором графе
                    
                    if (counter == 1)
                    {
                        ScIterator5Ptr it5_3 = m_memoryCtx.Iterator5(   // итератор для нахождения ребра между second color во втором графе
                            newNodes[i].secondColor,
                            ScType::EdgeUCommonConst,
                            newNodes[j].secondColor,
                            ScType::EdgeAccessConstPosPerm,
                            graph2);
                        SC_LOG_ERROR("smth4_1");
                        while (it5_3->Next())
                        {
                            SC_LOG_ERROR("3!!!!!!!");
                            addResultEdges(newNodes, newEdges, graph1, graph2, i, j);
                        }

                    }

                    if (counter == 1)
                    {
                        ScIterator5Ptr it5_4 = m_memoryCtx.Iterator5(   // обратный от верхнего, просто повторение, для неориентированного графа
                            newNodes[j].secondColor,
                            ScType::EdgeUCommonConst,
                            newNodes[i].secondColor,
                            ScType::EdgeAccessConstPosPerm,
                            graph2);
                        SC_LOG_ERROR("smth4_2");
                        while (it5_4->Next())
                        {
                            SC_LOG_ERROR("4!!!!!!!");
                            addResultEdges(newNodes, newEdges, graph1, graph2, i, j);
                            
                        }

                    }
                    
                    // ниже 2 итератора для пустых рёбер; первое число не соединено со вторым в первом графе
                    // в качестве пустышки(ребра которого нет) будет ребро ScType::EdgeUCommonVar, потому что платформа почему-то не видит точку, если она не соеденина с чем-либо

                    if (counter == 0)
                    {
                        ScIterator5Ptr it5_5 = m_memoryCtx.Iterator5(   // итератор для нахождения ребра(а точнее того, что его "нету") между first color в первом графе
                            newNodes[i].firstColor,
                            ScType::EdgeUCommonVar,
                            newNodes[j].firstColor,
                            ScType::EdgeAccessConstPosPerm,
                            graph1);
                        SC_LOG_ERROR("smth4_1");
                        while (it5_5->Next())
                        {
                            SC_LOG_ERROR("5!!!!!!!");
                            addResultEdges(newNodes, newEdges, graph2, graph1, i, j);
                        }

                    }

                    if (counter == 0)
                    {
                        ScIterator5Ptr it5_6 = m_memoryCtx.Iterator5(   // обратный от верхнего, просто повторение, для неориентированного графа
                            newNodes[j].firstColor,
                            ScType::EdgeUCommonVar,
                            newNodes[i].firstColor,
                            ScType::EdgeAccessConstPosPerm,
                            graph1);
                        SC_LOG_ERROR("smth4_2");
                        while (it5_6->Next())
                        {
                            SC_LOG_ERROR("6!!!!!!!");
                            addResultEdges(newNodes, newEdges, graph2, graph1, i, j);
                        }

                    }
                }

            }
        }
    }

    void LargeModularAgent::addResultEdges(vector <FinalNodes> &newNodes, ScAddrVector &newEdges, ScAddr const &graph1,
                                           ScAddr const &graph2, int i, int j) {
        ScAddr const &constNode1 = m_memoryCtx.HelperResolveSystemIdtf(newNodes[i].name, ScType::NodeConst);
        ScAddr const &constNode2 = m_memoryCtx.HelperResolveSystemIdtf(newNodes[j].name, ScType::NodeConst);

        ScAddr const &edge = m_memoryCtx.CreateEdge(ScType::EdgeUCommonConst, constNode1, constNode2);


        newEdges.push_back(edge);
    }


    void LargeModularAgent::processing(vector <FinalNodes> &newNodes,
                                       ScAddr const &graph1,
                                       ScAddr const &graph2) {
        ScIterator3Ptr it3_1 = m_memoryCtx.Iterator3(
                graph1,
                ScType::EdgeAccessConstPosPerm,
                ScType::NodeConst);

        while (it3_1->Next()) {
            ScIterator3Ptr it3_2 = m_memoryCtx.Iterator3(
                    graph2,
                    ScType::EdgeAccessConstPosPerm,
                    ScType::NodeConst);

            while (it3_2->Next()) {
                FinalNodes vec;
                vec.firstColor = it3_1->Get(2);
                vec.secondColor = it3_2->Get(2);
                vec.name = m_memoryCtx.HelperGetSystemIdtf(it3_1->Get(2)) + "_" +
                           m_memoryCtx.HelperGetSystemIdtf(it3_2->Get(2));
                newNodes.push_back(vec);
            }

        }
        for (int i = 0; i < newNodes.size(); i++) {             //выводит названия вершин в консоль
            SC_LOG_ERROR(newNodes[i].name);
            SC_LOG_ERROR(m_memoryCtx.HelperGetSystemIdtf(newNodes[i].firstColor));
            SC_LOG_ERROR(m_memoryCtx.HelperGetSystemIdtf(newNodes[i].secondColor));
            SC_LOG_ERROR("----");
        }
        SC_LOG_ERROR("Vertices creation end.");
    }
}
