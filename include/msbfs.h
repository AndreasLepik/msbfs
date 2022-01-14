#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include "bfs.h"

using namespace std;

class MSBFS : public BFS
{
  void run(Graph &graph, vector<int> sources)
  {
    cout << "Runnig MBFS..." << endl;

    // have to change to ordered set in order to do set difference?
    unordered_map<int, set<int>> seen(sources.size());
    // {(v => { source })}
    unordered_multimap<int, set<int>> visit;
    unordered_multimap<int, set<int>> visitNext;
    set<int> visitKeys;
    set<int> visitNextKeys;

    for (auto source : sources)
    {
      seen.insert(make_pair(source, set<int>{source}));
      visit.insert(make_pair(source, set<int>{source}));
      visitKeys.insert(source);
    }

    while (visit.size() > 0)
    {
      for (auto v : visitKeys)
      {
        // cout << node.first << ", " << node.second << endl;
        set<int> neighbours;
        auto incomingNodes = visit.equal_range(v);
        for (auto n = incomingNodes.first; n != incomingNodes.second; ++n)
        {
          neighbours.merge(n->second);
        }

        for (auto n : graph.getEdges(v))
        {
          set<int> D;
          auto nSeen = seen.find(n);
          if (nSeen == seen.end())
          {
            D = neighbours;
          }
          else
          {
            set_difference(neighbours.begin(),
                           neighbours.end(),
                           nSeen->second.begin(),
                           nSeen->second.end(),
                           inserter(D, D.begin()));
          }
          // D = neighbours \ seen.at(n);
          if (D.size() > 0)
          {
            visitNext.insert(make_pair(n, D));
            visitNextKeys.insert(n);
            auto nSeen = seen.find(n);
            if (nSeen == seen.end()) {
              seen.insert(make_pair(n, D));
            } else {
              seen.at(n).merge(D);
            }

            // do actual BFS calculation here
            cout << n << endl;
          }
        }
      }
      visit = visitNext;
      visitKeys = visitNextKeys;
      visitNext.clear();
      visitNextKeys.clear();
      cout << "+" << endl;
    }
  };
};