/**
 * field.cpp/h
 * These files contains the the code used to generate the field graph
 * Pointers to these variables used throughout code for navigation
 * 
 * Constant values defined in header are derived from official field drawings, with small tweaks to improve positioning in GUI
 * All values are in inches, as those are the provided units
 * 
 * The following drawing was used in addition to the Game Manual
 * https://i.imgur.com/1d51oAV.png
 * https://firstfrc.blob.core.windows.net/frc2016manuals/GameManual/FRC-2016-game-manual-02.pdf 
 */

#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include "../robot.h"
#include "../utils/LinkedList.h"
#include "../utils/Graph.h"
#include "field.h"

namespace Field {

    // Create nodes based on various constants from header file

    /**
     * RED NODES
     */
    Fieldpoint redTowerTop = Fieldpoint(
        RED_TOWER_X+TOWER_OFFSET_X, 
        RED_TOWER_Y+TOWER_OFFSET_Y,
        Alliance::RED, 
        Fieldpoint::Type::TOWER
    );
    Fieldpoint redTowerBottom = Fieldpoint(
        RED_TOWER_X+TOWER_OFFSET_X, 
        RED_TOWER_Y-TOWER_OFFSET_Y,
        Alliance::RED, 
        Fieldpoint::Type::TOWER
    );

    Defense redDefenses[DEFENSE_COUNT] = {
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(0*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(1*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(2*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(3*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(4*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        )
    };

    Fieldpoint redPassage[PASSAGE_COUNT] = {
        Fieldpoint(
            FIELD_LENGTH-0*SECRET_PASSAGE_LENGTH/3,
            FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
            Alliance::RED,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            FIELD_LENGTH-SECRET_PASSAGE_LENGTH/3,
            FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
            Alliance::RED,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            FIELD_LENGTH-2*SECRET_PASSAGE_LENGTH/3,
            FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
            Alliance::RED,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            FIELD_LENGTH-3*SECRET_PASSAGE_LENGTH/3,
            FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
            Alliance::RED,
            Fieldpoint::Type::RESTRICTED
        )
    };

    Fieldpoint redCourtyard[COURTYARD_COUNT] = {
        Fieldpoint(
            COURTYARD_OFFSET,
            redDefenses[1].y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            COURTYARD_OFFSET*1.5,
            RED_TOWER_Y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            COURTYARD_OFFSET,
            redDefenses[4].y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        )
    };

    /**
     * BLUE NODES
     */
    Fieldpoint blueTowerTop = Fieldpoint(
        BLUE_TOWER_X-TOWER_OFFSET_X,
        BLUE_TOWER_Y+TOWER_OFFSET_Y,
        Alliance::BLUE,
        Fieldpoint::Type::TOWER
    );
    Fieldpoint blueTowerBottom = Fieldpoint(
        BLUE_TOWER_X - TOWER_OFFSET_X,
        BLUE_TOWER_Y - TOWER_OFFSET_Y,
        Alliance::BLUE,
        Fieldpoint::Type::TOWER
    );

    Defense blueDefenses[DEFENSE_COUNT] = {
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (0*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (1*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (2*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (3*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (4*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
    };

    Fieldpoint bluePassage[PASSAGE_COUNT] = {
        Fieldpoint(
            0*SECRET_PASSAGE_LENGTH/3,
            SECRET_PASSAGE_WIDTH/2,
            Alliance::BLUE,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            SECRET_PASSAGE_LENGTH/3,
            SECRET_PASSAGE_WIDTH/2,
            Alliance::BLUE,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            2*SECRET_PASSAGE_LENGTH/3,
            SECRET_PASSAGE_WIDTH/2,
            Alliance::BLUE,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            3*SECRET_PASSAGE_LENGTH/3,
            SECRET_PASSAGE_WIDTH/2,
            Alliance::BLUE,
            Fieldpoint::Type::RESTRICTED
        )
    };

    Fieldpoint blueCourtyard[COURTYARD_COUNT] = {
        Fieldpoint(
            FIELD_LENGTH-COURTYARD_OFFSET,
            blueDefenses[1].y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH-COURTYARD_OFFSET*1.5,
            BLUE_TOWER_Y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH-COURTYARD_OFFSET,
            blueDefenses[4].y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        )
    };

    /**
     * NEUTRAL
     */
    Fieldpoint centreBalls[CENTRE_BALL_COUNT] = {
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*1,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*2,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*3,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*4,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*5,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*6,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        )
    };

    /**
     * Initialise a graph of the field
     * This will automatically build the graph from the various predefined fieldpoints
     * 
     */
    Graph *initGraph(){
        Graph *g = new Graph();
        g->addNode(&redTowerTop);
        g->addNode(&redTowerBottom);
        g->addNodes(redDefenses, DEFENSE_COUNT);
        g->addNodes(redPassage, PASSAGE_COUNT);
        g->addNodes(redCourtyard, COURTYARD_COUNT);

        g->addNode(&blueTowerTop);
        g->addNode(&blueTowerBottom);
        g->addNodes(blueDefenses, DEFENSE_COUNT);
        g->addNodes(bluePassage, PASSAGE_COUNT);
        g->addNodes(blueCourtyard, COURTYARD_COUNT);

        g->addNodes(centreBalls, CENTRE_BALL_COUNT);

        /**
         * RED NODES
         */
        {
            // Add edges for red courtyard nodes
            g->addEdge(&redCourtyard[0], &redTowerTop);
            g->addDefenseEdge(&redCourtyard[0], &redDefenses[0], false);
            g->addDefenseEdge(&redCourtyard[0], &redDefenses[1], false);
            g->addDefenseEdge(&redCourtyard[0], &redDefenses[2], false);
            g->addEdge(&redCourtyard[0], &redCourtyard[1]);
            g->addEdge(&redCourtyard[0], &redCourtyard[2]);
            g->addDefenseEdge(&redCourtyard[1], &redDefenses[0], false);
            g->addDefenseEdge(&redCourtyard[1], &redDefenses[1], false);
            g->addDefenseEdge(&redCourtyard[1], &redDefenses[2], false);
            g->addDefenseEdge(&redCourtyard[1], &redDefenses[3], false);
            g->addDefenseEdge(&redCourtyard[1], &redDefenses[4], false);
            g->addEdge(&redCourtyard[2], &redTowerBottom);
            g->addDefenseEdge(&redCourtyard[2], &redDefenses[3], false);
            g->addDefenseEdge(&redCourtyard[2], &redDefenses[4], false);
            g->addEdge(&redCourtyard[1], &redCourtyard[0]);
            g->addEdge(&redCourtyard[1], &redCourtyard[2]);

            // Add edges for red defenses and centre field
            g->addDefenseEdge(&redDefenses[0], &centreBalls[5], true);
            g->addDefenseEdge(&redDefenses[1], &centreBalls[5], true);
            g->addDefenseEdge(&redDefenses[1], &centreBalls[4], true);
            g->addDefenseEdge(&redDefenses[1], &centreBalls[3], true);
            g->addDefenseEdge(&redDefenses[2], &centreBalls[3], true);
            g->addDefenseEdge(&redDefenses[2], &centreBalls[2], true);
            g->addDefenseEdge(&redDefenses[3], &centreBalls[2], true);
            g->addDefenseEdge(&redDefenses[3], &centreBalls[1], true);
            g->addDefenseEdge(&redDefenses[4], &centreBalls[1], true);
            g->addDefenseEdge(&redDefenses[4], &centreBalls[0], true);

            // Add edges for red secret passage
            g->addEdge(&redPassage[0], &redPassage[1]);
            g->addEdge(&redPassage[1], &redPassage[2]);
            g->addEdge(&redPassage[2], &redPassage[3]);
            g->addEdge(&redPassage[3], &centreBalls[5]);
            g->addEdge(&redPassage[3], &centreBalls[4]);
            g->addEdge(&redPassage[3], &centreBalls[3]);
        }

        /**
         * BLUE NODES
         * CentreBalls are flipped, so indices are 5-redVal
         */
        {
            // Add edges for blue courtyard nodes
            g->addEdge(&blueCourtyard[0], &blueTowerBottom);
            g->addDefenseEdge(&blueCourtyard[0], &blueDefenses[0], false);
            g->addDefenseEdge(&blueCourtyard[0], &blueDefenses[1], false);
            g->addEdge(&blueCourtyard[0], &blueCourtyard[1]);
            g->addEdge(&blueCourtyard[0], &blueCourtyard[2]);
            g->addDefenseEdge(&blueCourtyard[1], &blueDefenses[0], false);
            g->addDefenseEdge(&blueCourtyard[1], &blueDefenses[1], false);
            g->addDefenseEdge(&blueCourtyard[1], &blueDefenses[2], false);
            g->addDefenseEdge(&blueCourtyard[1], &blueDefenses[3], false);
            g->addDefenseEdge(&blueCourtyard[1], &blueDefenses[4], false);
            g->addEdge(&blueCourtyard[2], &blueTowerTop);
            g->addDefenseEdge(&blueCourtyard[2], &blueDefenses[3], false);
            g->addDefenseEdge(&blueCourtyard[2], &blueDefenses[4], false);
            g->addEdge(&blueCourtyard[1], &blueCourtyard[0]);
            g->addEdge(&blueCourtyard[1], &blueCourtyard[2]);

            // Add edges for blue defenses and centre field
            g->addDefenseEdge(&blueDefenses[0], &centreBalls[5-5], true);
            g->addDefenseEdge(&blueDefenses[1], &centreBalls[5-5], true);
            g->addDefenseEdge(&blueDefenses[1], &centreBalls[5-4], true);
            g->addDefenseEdge(&blueDefenses[1], &centreBalls[5-3], true);
            g->addDefenseEdge(&blueDefenses[2], &centreBalls[5-3], true);
            g->addDefenseEdge(&blueDefenses[2], &centreBalls[5-2], true);
            g->addDefenseEdge(&blueDefenses[3], &centreBalls[5-2], true);
            g->addDefenseEdge(&blueDefenses[3], &centreBalls[5-1], true);
            g->addDefenseEdge(&blueDefenses[4], &centreBalls[5-1], true);
            g->addDefenseEdge(&blueDefenses[4], &centreBalls[5-0], true);

            // Add edges for blue secret passage
            g->addEdge(&bluePassage[0], &bluePassage[1]);
            g->addEdge(&bluePassage[1], &bluePassage[2]);
            g->addEdge(&bluePassage[2], &bluePassage[3]);
            g->addEdge(&bluePassage[3], &centreBalls[5-5]);
            g->addEdge(&bluePassage[3], &centreBalls[5-4]);
            g->addEdge(&bluePassage[3], &centreBalls[5-3]);
        }

        /**
         * NEUTRAL
         */
        {
            // Connect centreBalls to eachother
            g->addEdge(&centreBalls[0], &centreBalls[1]);
            g->addEdge(&centreBalls[1], &centreBalls[2]);
            g->addEdge(&centreBalls[2], &centreBalls[3]);
            g->addEdge(&centreBalls[3], &centreBalls[4]);
            g->addEdge(&centreBalls[4], &centreBalls[5]);
        }
        
        return g;
    }

    void toGraphML(Graph *g, const char* filename){
        FILE *f = fopen(filename, "w");
        // Add config lines taken from exported file
        fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<!--Created by yFiles for HTML 2.3.0.3-->\n<graphml xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://www.yworks.com/xml/schema/graphml.html/2.0/ygraphml.xsd \" xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:demostyle=\"http://www.yworks.com/yFilesHTML/demos/FlatDemoStyle/1.0\" xmlns:icon-style=\"http://www.yworks.com/yed-live/icon-style/1.0\" xmlns:bpmn=\"http://www.yworks.com/xml/yfiles-bpmn/2.0\" xmlns:demotablestyle=\"http://www.yworks.com/yFilesHTML/demos/FlatDemoTableStyle/1.0\" xmlns:uml=\"http://www.yworks.com/yFilesHTML/demos/UMLDemoStyle/1.0\" xmlns:compat=\"http://www.yworks.com/xml/yfiles-compat-arrows/1.0\" xmlns:GraphvizNodeStyle=\"http://www.yworks.com/yFilesHTML/graphviz-node-style/1.0\" xmlns:VuejsNodeStyle=\"http://www.yworks.com/demos/yfiles-vuejs-node-style/1.0\" xmlns:explorer-style=\"http://www.yworks.com/data-explorer/1.0\" xmlns:y=\"http://www.yworks.com/xml/yfiles-common/3.0\" xmlns:x=\"http://www.yworks.com/xml/yfiles-common/markup/3.0\" xmlns:yjs=\"http://www.yworks.com/xml/yfiles-for-html/2.0/xaml\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n\t<key id=\"d0\" for=\"node\" attr.type=\"int\" attr.name=\"zOrder\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-z-order/1.0/zOrder\"/>\n\t<key id=\"d1\" for=\"node\" attr.type=\"boolean\" attr.name=\"Expanded\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/folding/Expanded\">\n\t\t<default>true</default>\n\t</key>\n\t<key id=\"d2\" for=\"node\" attr.type=\"string\" attr.name=\"url\"/>\n\t<key id=\"d3\" for=\"node\" attr.type=\"string\" attr.name=\"description\"/>\n\t<key id=\"d4\" for=\"node\" attr.name=\"NodeLabels\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/NodeLabels\"/>\n\t<key id=\"d5\" for=\"node\" attr.name=\"NodeGeometry\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/NodeGeometry\"/>\n\t<key id=\"d6\" for=\"all\" attr.name=\"UserTags\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/UserTags\"/>\n\t<key id=\"d7\" for=\"node\" attr.name=\"NodeStyle\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/NodeStyle\"/>\n\t<key id=\"d8\" for=\"node\" attr.name=\"NodeViewState\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/folding/1.1/NodeViewState\"/>\n\t<key id=\"d9\" for=\"edge\" attr.type=\"string\" attr.name=\"url\"/>\n\t<key id=\"d10\" for=\"edge\" attr.type=\"string\" attr.name=\"description\"/>\n\t<key id=\"d11\" for=\"edge\" attr.name=\"EdgeLabels\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/EdgeLabels\"/>\n\t<key id=\"d12\" for=\"edge\" attr.name=\"EdgeGeometry\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/EdgeGeometry\"/>\n\t<key id=\"d13\" for=\"edge\" attr.name=\"EdgeStyle\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/EdgeStyle\"/>\n\t<key id=\"d14\" for=\"edge\" attr.name=\"EdgeViewState\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/folding/1.1/EdgeViewState\"/>\n\t<key id=\"d15\" for=\"port\" attr.name=\"PortLabels\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/PortLabels\"/>\n\t<key id=\"d16\" for=\"port\" attr.name=\"PortLocationParameter\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/PortLocationParameter\">\n\t\t<default>\n\t\t\t<x:Static Member=\"y:FreeNodePortLocationModel.NodeCenterAnchored\"/>\n\t\t</default>\n\t</key>\n\t<key id=\"d17\" for=\"port\" attr.name=\"PortStyle\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/PortStyle\">\n\t\t<default>\n\t\t\t<x:Static Member=\"y:VoidPortStyle.Instance\"/>\n\t\t</default>\n\t</key>\n\t<key id=\"d18\" for=\"port\" attr.name=\"PortViewState\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/folding/1.1/PortViewState\"/>\n\t<key id=\"d19\" attr.name=\"SharedData\" y:attr.uri=\"http://www.yworks.com/xml/yfiles-common/2.0/SharedData\"/>\n\t<data key=\"d19\">\r\n\t\t<y:SharedData>\r\n\t\t\t<y:ExteriorLabelModel x:Key=\"1\" Insets=\"5\"/>\r\n\t\t\t<y:CompositeLabelModelParameter x:Key=\"2\">\r\n\t\t\t\t<y:CompositeLabelModelParameter.Parameter>\r\n\t\t\t\t\t<y:ExteriorLabelModelParameter Position=\"South\" Model=\"{y:GraphMLReference 1}\"/>\r\n\t\t\t\t</y:CompositeLabelModelParameter.Parameter>\r\n\t\t\t\t<y:CompositeLabelModelParameter.Model>\r\n\t\t\t\t\t<y:CompositeLabelModel>\r\n\t\t\t\t\t\t<y:CompositeLabelModel.LabelModels>\r\n\t\t\t\t\t\t\t<y:GraphMLReference ResourceKey=\"1\"/>\r\n\t\t\t\t\t\t\t<y:InteriorLabelModel/>\r\n\t\t\t\t\t\t\t<y:FreeNodeLabelModel/>\r\n\t\t\t\t\t\t</y:CompositeLabelModel.LabelModels>\r\n\t\t\t\t\t</y:CompositeLabelModel>\r\n\t\t\t\t</y:CompositeLabelModelParameter.Model>\r\n\t\t\t</y:CompositeLabelModelParameter>\r\n\t\t\t<yjs:DefaultLabelStyle x:Key=\"3\" verticalTextAlignment=\"BOTTOM\" horizontalTextAlignment=\"CENTER\" textFill=\"BLACK\">\r\n\t\t\t\t<yjs:DefaultLabelStyle.font>\r\n\t\t\t\t\t<yjs:Font fontSize=\"12\" fontFamily=\"'Arial'\"/>\r\n\t\t\t\t</yjs:DefaultLabelStyle.font>\r\n\t\t\t</yjs:DefaultLabelStyle>\r\n\t\t</y:SharedData>\r\n\t</data>");
        fprintf(f, "<graph id=\"G\" edgedefault=\"undirected\">\n");
        // Add nodes to the graph
        for(auto i : g->nodes){
            Fieldpoint *p = i.data;
            fprintf(f, "\t<node id=\"%d\">\n", i.index);
            fprintf(f, "\t<data key=\"d5\">\n\t\t<y:RectD X=\"%d\" Y=\"%d\" Width=\"10\" Height=\"10\"/>\n\t</data>\n", p->x, p->y);
            // Set node colour based on ownership
            switch(p->alliance){
                case Alliance::RED:
                    fprintf(f, "\t<data key=\"d7\">\n\t\t<yjs:ShapeNodeStyle stroke=\"#FFFF0000\" fill=\"#FFFF0000\"/>\n\t\t</data>");
                    break;
                case Alliance::BLUE:
                    fprintf(f, "\t<data key=\"d7\">\n\t\t<yjs:ShapeNodeStyle stroke=\"#FF0000FF\" fill=\"#FF0000FF\"/>\n\t\t</data>");
                    break;
                default:
                    fprintf(f, "\t<data key=\"d7\">\n\t\t<yjs:ShapeNodeStyle stroke=\"#FF4A2A7C\" fill=\"#FF4A2A7C\"/>\n\t\t</data>");
                    break;
            }
            // Add index under node
            fprintf(f, "\t<data key=\"d4\">\n\t\t<x:List>\n\t\t\t<y:Label LayoutParameter=\"{y:GraphMLReference 2}\" Style=\"{y:GraphMLReference 3}\">\n\t\t\t\t<y:Label.Text>%d</y:Label.Text>\n\t\t\t</y:Label>\n\t\t</x:List>\n\t</data>\n\t", p->index);
            fprintf(f, "\t<port name=\"p0\"/>\n</node>\n");
        }
        // Add edges between nodes
        for(auto i : g->adjacency) {
            LinkedList<Graph::Edge> *l = i.data;
            for(auto j : *l){
                fprintf(f, "\t<edge id=\"%d%d\" source=\"%d\" target=\"%d\" sourceport=\"p0\" targetport=\"p0\">\n", i.index, j.index, i.index, j.data.end->index);
                
                fprintf(f, "\t<data key=\"d13\">\n\t\t<yjs:PolylineEdgeStyle stroke=\"#0000000\">\n\t\t<yjs:PolylineEdgeStyle.targetArrow>\n\t\t\t<yjs:Arrow type=\"TRIANGLE\" stroke=\"#FF000000\" fill=\"BLACK\"/>\n\t\t</yjs:PolylineEdgeStyle.targetArrow>\n\t\t<yjs:PolylineEdgeStyle.sourceArrow>\n\t\t\t<yjs:Arrow type=\"NONE\" stroke=\"#FF000000\" fill=\"BLACK\"/>\n\t\t</yjs:PolylineEdgeStyle.sourceArrow>\n\t\t</yjs:PolylineEdgeStyle>\n\t</data>\n");
                // fprintf(f, "\t<data key=\"d11\">\n\t\t<x:List>\n\t\t\t<y:Label Style=\"{y:GraphMLReference 3}\">\n\t\t\t\t<y:Label.Text>%d</y:Label.Text>\n\t\t\t\t<y:Label.LayoutParameter>\n\t\t\t\t\t<y:SmartEdgeLabelModelParameter Distance=\"5\">\n\t\t\t\t\t\t<y:SmartEdgeLabelModelParameter.Model>\n\t\t\t\t\t\t\t<y:SmartEdgeLabelModel/>\n\t\t\t\t\t\t</y:SmartEdgeLabelModelParameter.Model>\n\t\t\t\t\t</y:SmartEdgeLabelModelParameter>\n\t\t\t\t</y:Label.LayoutParameter>\n\t\t\t</y:Label>\n\t\t</x:List>\n\t</data>\n\t", e.distance);

                fprintf(f, "\t</edge>\n");
            }
        }
        fprintf(f, "</graph>\n</graphml>");
        fclose(f);
    }

    void print(Graph *g, bool showdots){
        // Array of nodes, has h/w of 1/10th size, each postion has 3 characters
        char out[FIELD_LENGTH/10][FIELD_WIDTH/10][3];

        // Fill array with spaces, include dots if enabled
        for(int i=0; i<FIELD_WIDTH/10; i++){
            for(int j=0; j<FIELD_LENGTH/10; j++){
                out[j][i][0]=showdots ? '.' : ' ';
                out[j][i][1]=' ';
                out[j][i][2]=' ';
            }
        }

        int x,y;
        // For each node, update the apropriate position int he array with information
        for(int i = 0; i<g->nodes.size(); i++){
            x = g->nodes[i]->x/10;
            y = g->nodes[i]->y/10;

            // Set alliance letter
            switch(g->nodes[i]->alliance){
                case Alliance::RED:
                    out[x][y][0] = 'R';
                    break;
                case Alliance::BLUE:
                    out[x][y][0] = 'B';
                    break;
                default:
                    out[x][y][0] = ' ';
                    break;
            }

            // Set type letters
            switch(g->nodes[i]->type){
                case Fieldpoint::Type::TOWER:
                    out[x][y][1]='T';
                    out[x][y][2]='W';
                    break;
                case Fieldpoint::Type::DEFENSE:
                    out[x][y][1]='D';
                    out[x][y][2]='F';
                    break;
                case Fieldpoint::Type::RESTRICTED:
                    out[x][y][1]='N';
                    out[x][y][2]='R';
                    break;
                case Fieldpoint::Type::SHOTNODE:
                    out[x][y][1]='S';
                    out[x][y][2]='N';
                    break;
                default:
                    out[x][y][1]='N';
                    out[x][y][2]=' ';
                    break;
            }
        }

        // Print out the array
        for(int i=0; i<FIELD_WIDTH/10; i++){
            printf("%03d|",i*10);
            for(int j=0; j<FIELD_LENGTH/10; j++){
                printf("%c%c%c",out[j][i][0],out[j][i][1],out[j][i][2]);
            }
            printf("|\n");
        }
    }
}