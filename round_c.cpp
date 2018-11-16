#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::make_tuple;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

using ll = long long;

class FenwickTree {
public:
    explicit FenwickTree(int n) : data(n) {
        for (int i = 0; i < n; ++i) {
            data[i] = i;
        }
    }

    int find(int loc) const {
        int iter = loc;
        while (data[iter] != iter) iter = data[iter];
        int parent = iter;
        iter = loc;
        while (data[iter] != iter) {
            std::tie(iter, data[iter]) = make_tuple(data[iter], parent);
        }
        return parent;
    }

    bool merge(int prefer, int sub) {
        prefer = find(prefer);
        sub = find(sub);
        if (sub == prefer) {
            return false;
        } else {
            data[sub] = prefer;
            return true;
        }
    }

    bool isLinked(int a, int b) const {
        return find(a) != find(b);
    }

private:
    mutable vector<int> data;
};

class Solution {
public:
    Solution() {
        generate();
        gen_graph();
    }

    enum GridType {
        Wall,
        Potion,
        Trap
    };

    GridType get_type(int id) {
        ll value = matrix[id];
        if (value == -100000) {
            return Wall;
        } else if (value < 0) {
            return Trap
        } else {
            return Potion;
        }
    }

    GridType get_type(int i, int j) {
        int id = get_id(i, j);
        return get_type(id);
    }

    void gen_graph() {
        FenwickTree tree(N *M);
        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < M - 1; ++j) {
                int grid = get_id(i, j);
                int right_grid = get_id(i, j + 1);
                int down_grid = get_id(i + 1, j);
                if (get_type(grid) == Potion) {
                    if (get_type(right_grid) == Potion) {
                        tree.merge(grid, right_grid);
                    }
                    if (get_type(down_grid) == Potion) {
                        tree.merge(grid, down_grid);
                    }
                }
            }
        }

        map<int, int> mapping;
        set<int> traps;
        int trap_id_gen = 0;
        int potion_id_gen = 15;
        for (int i = 0; i < N - 1; ++i) {
            for (int j = 1; j < M - 1; ++j) {
                int grid = get_id(i, j);
                auto type = get_type(grid);
                switch (type) {
                    case Wall:
                        continue;
                    case Potion: {
                        int potion_id = tree.find(grid);
                        if (!mapping.count(potion_id)) {
                            mapping[potion_id] = potion_id_gen++;
                        }
                        potion_id = mapping[potion_id];
                        value[potion_id] += matrix[grid];
                        break;
                    }
                    case Trap: {
                        int trap_id = grid;
                        if (!mapping.count(trap_id)) {
                            mapping[trap_id] = trap_id_gen++;
                        }
                        trap_id = mapping[trap_id];
                        value[trap_id] += matrix[trap_id];
                        traps.insert(trap_id);
                        break;
                    }
                }
            }
        }

        this->trap_count = trap_id_gen;   // todo
        this->potion_count = potion_id_gen; // todo
        for (auto trap: traps) {
            auto diffs = {-M, +M, -1, +1};
            for (auto diff:diffs) {
                int neighbor = trap + diff;
                if (get_type(neighbor) == Wall) continue;
                int v1 = mapping[trap];
                int v2 = mapping[neighbor];
                graph[v1].insert(v2);
                graph[v2].insert(v1);
            }
        }
        auto[x, y] = source;
        this->src_id = mapping[get_id(x, y)]; // todo
        std::tie(x, y) = dest;
        this->dst_id = mapping[get_id(x, y)]; // todo

    }

    ll calculate_life(const FenwickTree &tree){
        ll life = init_life;
        for(int i = 0; i < trap_count; ++i){
            if(tree.isLinked(src_id, i)) {
                life += value[i];
            }
        }
        for(int i = 15; i < potion_count; ++i) {
            if(tree.isLinked(src_id, i)) {
                life += value[i];
            }
        }
        return life;
    }

    void explore(const FenwickTree &last_tree, ll trap_vector) {
        if(record.count(trap_vector)){
            return;
        }
        auto life = calculate_life(last_tree);
        record[trap_vector] = life;
        if(last_tree.isLinked(src_id, dst_id)){
            max_life = std::max(max_life, life);
        }

        int src_id = last_tree.find(this->src_id);
        for (int trap_id = 0; trap_id < trap_count; ++trap_id) {
            if (trap_vector & (1 << trap_id) == 1) {
                continue;
            }
            for (auto nei: graph[trap_id]) {
                if (last_tree.isLinked(nei, src_id)) {
                    goto deal;
                }
            }
            continue;
            deal:
            if (life < value[trap_id]) {
                continue;
            }
            FenwickTree new_tree = last_tree;
            ll new_vector = trap_vector | (1 << trap_id)
            for (auto nei: graph[trap_id]) {
                if( nei >= 15 || (1 << nei) & trap_vector == 1){
                    new_tree.merge(nei, trap_id);
                }
            }
            explore(new_tree, new_vector);
        }
    }

    long long workload() {
        FenwickTree init(potion_count + 15);
        max_life = 0;
        explore(init, 0);
        return max_life;
    }

private:
    int get_id(int n, int m) {
        return n * M + m;
    }

    ll &get_raw_value(int n, int m) {
        return matrix[get_id(n, m)];
    }

    void generate() {
        cin >> N >> M;
        cin >> init_life;
        cin >> source.first >> source.second;
        cin >> dest.first >> dest.second;
        N += 2;
        M += 2;
        matrix.resize(N * M, -100000);
        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < M - 1; ++j) {
                cin >> get_raw_value(i, j);
            }
        }

    }

private:
    int N, M;
    ll init_life;
    pair<int, int> source;
    pair<int, int> dest;
    vector<ll> matrix;

private:
    map<int, ll> record;
    ll max_life;
private:
    int trap_count;
    int potion_count;
    int src_id;
    int dst_id;
    map<int, set<int>> graph; // todo
    map<int, ll> value; // todo

};

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        auto ans = Solution().workload();
        cout << "Case #" << i + 1
             << ": "                 //
             //  << std::fixed << std::setprecision(6) //
             << ans << std::endl;    //
    }
}
