#include <bits/stdc++.h>
#include <ctime>
#define ll long long
#define all(s) s.begin(),s.end()
#define rall(s) s.rbegin(),s.rend()
#define pb push_back
#define ft first
#define sc second
#define pi pair<ll,ll>
#define vi vector<ll>
#define sz(s) s.size()
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<ll, null_type, less<ll>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;
const ll N = 1e5+5,M = 18,MOD = 1e9+7,INF = 2e18;
int dx[] = {-1,1, 0, 0},Dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};;
int dy[] = {0, 0, 1, -1},Dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
vector< pair<int,int> > p;
unordered_map<int,set<int>> follow,followed;
string s;
int id;
int main()
{
    //ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    clock_t starttime , endtime;
    time(&starttime);
    ifstream myfile("twitter.csv");

    while(getline(myfile,s))                    // read information from file.
    {
        int u = 0,v = 0, tmp = 0;
        for(int i = 0 ;i < s.size() ;++i)       // Iterating over the line readed ( O(s.size()) )
        {
            if(s[i] == ',')
            {
                u = tmp;                        // save first ID
                tmp = 0;
                continue;
            }
            tmp = (tmp * 10) + (s[i] - '0');
        }
        v = tmp;                                // save second ID
        follow[u].insert(v);                    // make directed edge between first ID and second ID ( O(1) )
        followed[v].insert(u);                  // reverse edge between first ID and second ID ( O(1) )
    }

    for(auto it:followed)                             // iterate over reversed graph ( O(followed.size()) )
        p.push_back({it.second.size(),it.first});      // save the number of followers of each ID and ID

    sort(p.rbegin(),p.rend());                  // sort vector in Descending Order ( O(p.size() * LOG (p.size())) )

    for(int i = 0 ; i < (int)10 ;++i)
      cout << "User with ID: " << p[i].second << " Has: " << p[i].first << " followers\n";
    //cout << p[41].second << ' ' << p[41].first << endl;
   //cout << p[1].second << ' ' << p[1].first << endl;
    time(&endtime);
     double time_taken = double (endtime - starttime);
   cout << "Running time: "<<time_taken<< endl;
   cin >> id;

    unordered_map<int,int> freq;
    vector<pair<int,int>> mx_freq;
    for(auto it:follow[id])                     // Iterating over the the IDs followed by input ID ( O(follow[id].size()) )
    {
        for(auto it2:followed[it]){             // Iterating over the the IDs follow child of input ID ( O(follow[it].size()) )
            if(follow[it2].count(id) || it2 == id) continue;        // check if specific ID follow input ID O( LOG(follow[it2].SIZE()) )
            freq[it2]++;
        }
    }

    for(auto it:freq)                            // Iterating over mutual friends O(freq.size())
        mx_freq.push_back({it.second,it.first});

    sort(mx_freq.rbegin(),mx_freq.rend());      // sort vector in Descending Order ( O(mx_freq.size() * LOG (mx_freq.size())) )

    for(int i = 0; i < 5 ;++i)
        cout <<"You may want to follow user with ID: " << mx_freq[i].second << endl;


    return 0;
}
