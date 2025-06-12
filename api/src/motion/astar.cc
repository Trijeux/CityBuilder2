#include "motion/AStar.h"

#include <array>
#include <iostream>
#include <queue>

#include "motion/path.h"

namespace api::motion {

    struct AStarNode {
        sf::Vector2f position;
        float g;
        float h;
        float f;

        AStarNode* previous_node;

        AStarNode(sf::Vector2f position, float g, float h, AStarNode* prev) : position(position),
                                                                              g(g),
                                                                              h(h),
                                                                              f(g + h),
                                                                              previous_node(prev)
                                                                              {


        }

        // A Star node are prioritize by the lowest f value
        friend bool operator<(AStarNode const &left, AStarNode const &right){
            return left.f > right.f;
        }
    };

    float heuristic(sf::Vector2f p1, sf::Vector2f p2){
        return (p2 - p1).length();
    }

    std::array<sf::Vector2f, 4> neighbours = {
        sf::Vector2f(0, 16),
        sf::Vector2f(16, 0),
        sf::Vector2f(0, -16),
        sf::Vector2f(-16, 0)
    };

    Path ReconstitutePath(AStarNode &start_node){
        Path path;
        std::vector<sf::Vector2f> pathPoints;
        AStarNode *current_node = &start_node;

        while (current_node != nullptr) {
            std::cout << "reconstiution point : " << current_node->position.x << ":" << current_node->position.y <<
                    std::endl;
            pathPoints.emplace_back(current_node->position);
            current_node = current_node->previous_node;
        }

        std::ranges::reverse(pathPoints);
        path.Fill(pathPoints);

        return path;
    }

    Path GetPath(sf::Vector2f start, sf::Vector2f end, std::vector<sf::Vector2f> walkableTiles){
        Path aStarPath;

        // Are start / end point in walkables tiles ?
        auto f = std::find(walkableTiles.begin(), walkableTiles.end(), start);
        if (f == walkableTiles.end()) {
            std::cout << "Start point not in walkable tiles" << std::endl;
            return aStarPath;
        }

        auto g = std::find(walkableTiles.begin(), walkableTiles.end(), end);
        if (g == walkableTiles.end()) {
            std::cout << "End point not in walkable tiles" << std::endl;
            return aStarPath;
        }

        // ---------------------------------------------
        std::vector<AStarNode> closedList;

        std::priority_queue<AStarNode> openList;
        openList.push(AStarNode(start, 0, heuristic(start, end), nullptr));

        while (!openList.empty()) {
            AStarNode currentNode = openList.top();
            openList.pop();

            std::cout << "current node : " << currentNode.position.x << ":" << currentNode.position.y << std::endl;

            if (currentNode.position == end) {
                std::cout << "Found path" << std::endl;
                return ReconstitutePath(currentNode);
            }

            for (auto neighbour: neighbours) {
                sf::Vector2f newPosition = currentNode.position + neighbour;

                auto f = std::find(walkableTiles.begin(), walkableTiles.end(), newPosition);

                if (f != walkableTiles.end()) {

                    auto g = std::find_if(
                        closedList.begin(),
                        closedList.end(),
                                        [&newPosition](const AStarNode &n) {
                                          return newPosition == n.position;
                                        }
                    );

                    // new node
                    AStarNode newNode = AStarNode(
                        newPosition, 
                        currentNode.g + 1, 
                        heuristic(newPosition, end), 
                        new AStarNode(currentNode)
                    );

                    if (g == closedList.end()) {
                      openList.push(newNode);
                    }
                    closedList.emplace_back(newNode);
                }
            }
        }

        return aStarPath;
    }
}
