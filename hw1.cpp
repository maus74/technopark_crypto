#include<iostream>
#include<algorithm>
#include <stdlib.h>  
#include<vector>
using namespace std;
typedef long long ll;
#define endl '\n'


vector<pair<string, ll>> A;

vector<ll> factorials;

void calc_factorials()
{
	factorials[0] = 1;
	factorials[1] = 1;
	for (ll i = 2; i < factorials.size(); i++)
	{
			factorials[i] = factorials[i - 1] * (i);
	}
}

vector<ll> find_k_permutation(ll k,ll n)
{
	ll cur = 1;
	vector<ll> result(n);
	for (ll i = 0; i < result.size(); i++)
	{
		result[i] = 1;
	}
	vector<ll> used(n + 1, 0);
	ll flag_end = 0;
	for (ll i = 0; i < n; i++)
	{
		if (flag_end == 1)
			break;

		for (ll k1 = 1; k1 <=n; k1++)
		{
			if (used[k1] == 0)
			{
				result[i] = k1;
				break;
			}
		}
		ll start = result[i];
		for (ll j = start; j < n; j++)
		{
			if (cur + factorials[n - (i + 1)] <= k)
			{
				cur += factorials[n - (i + 1)];
				result[i]++;
				continue;
			}
			else
			{
				if (used[result[i]] == 1)
				{
					for (ll k1 = 1; k1 <= n; k1++)
					{
						if (used[k1] != 1)
						{
							used[k1] = 1;
							result[i] = k1;
							break;
						}
					}
				}

				if (cur == k)
				{
					
					for (ll k1 = 0; k1 <= i; k1++)
					{
						used[result[k1]] = 1;
					}
					for (ll k1 = i + 1; k1 < result.size(); k1++)
					{
						for (ll k2 = 1; k2 < used.size(); k2++)
						{
							if (used[k2] == 0)
							{
								used[k2] = 1;
								result[k1] = k2;
								break;
							}
						}
					}
					flag_end = 1;
				}
				else
				{
					used[result[i]] = 1;
					break;
				}
			}

		}
	}
	return result;
}



int main(int argc, char* argv[])
{

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	setlocale(LC_ALL, "Russian");
	freopen(argv[2], "r", stdin);

	string cur;
	vector<string> data;
	vector<ll> permutation;
	ll ind = 1;

	ll numbilets = atoll(argv[4]), parameter = atoll(argv[6]);
	factorials.resize(numbilets+1);
	calc_factorials();
	parameter ^=  0x9e35C9b9;
	parameter ^= (parameter<<6);
	parameter ^= (parameter<<7);
	parameter ^= (parameter<<15);

	

	while (getline(cin, cur)) {
		data.push_back(cur);
	}

	ll cnt_permutations = factorials[numbilets];


	parameter = parameter % cnt_permutations;
	
	
	permutation = find_k_permutation(parameter, numbilets);
	
	for (ll i = 0; i < data.size(); i++)
	{
		cout << data[i]<<" "<<permutation[i]<<endl;
	}
	
	return 0;
}
