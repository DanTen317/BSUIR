#pragma once

#include <string>
#include <vector>

#include <sc-memory/kpm/sc_agent.hpp>
#include "keynodes/keynodes.hpp"
#include "LargeModularAgent.generated.hpp"

namespace exampleModule {

    struct FinalNodes
    {
        ScAddr firstColor;
        ScAddr secondColor;
        std::string name;
    };

    class LargeModularAgent : public ScAgent
    {
        SC_CLASS(Agent, Event(Keynodes::large_modular_agent, ScEvent::Type::AddOutputEdge))
        SC_GENERATED_BODY()

        void createResponseConstruction(ScAddrVector & newEdges, ScAddr const & graph1, ScAddr const & graph2);
        void detectEdges(std::vector<FinalNodes> & newNodes, ScAddrVector & newEdges, ScAddr const & graph1, ScAddr const & graph2);
        void addResultEdges(std::vector<FinalNodes> & newNodes, ScAddrVector & newEdges, ScAddr const & graph1, ScAddr const & graph2, int i, int j);

        void processing(std::vector<FinalNodes> & newNodes, ScAddr const & graph1, ScAddr const & graph2);
    };
}
