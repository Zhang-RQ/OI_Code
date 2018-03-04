// 1. 区间赋值
// 2. 区间取max
// 3. 区间取min
// 4. 插入一段区间
// 5. 删除一段区间
// 6. 将一段区间翻转
// 7. 将一段整体乘一个数
// 8. 区间求和
// 9. 区间求积

#include <cstdio>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;
const ll P=(ll)1E9+7;
const ll N = 100010;
ll n, m;

vector<ll> v;

ll tmp[N];

ll MaxSum(ll *v,ll n)
{
    ll sum=0,b=0;
    ll i;
    for (i=1;i<=n;i++)
    {
        if(b>0)
            b+=v[i];
        else
            b=v[i];
        if(b>sum)
            sum=b;
    }
    return sum % P;
}

signed main() {
	scanf("%lld%lld", &n, &m);
	v.push_back(-1);
	for(ll i = 1, x ; i <= n ; ++ i) {
		scanf("%lld", &x);
		v.push_back(x);
	}
	for(ll i = 1, op, l, r, val ; i <= m ; ++ i) {
		scanf("%lld", &op);

		if(op == 1) {
			// 1. 区间赋值
			scanf("%lld%lld%lld", &l, &r, &val);
			for(ll j = l ; j <= r ; ++ j) {
				v[j] = val;
			}
		}

		if(op == 2) {
			// 2. 区间取max
			scanf("%lld%lld", &l, &r);
			ll ans = v[l];
			for(ll j = l ; j <= r ; ++ j) ans = max(ans, v[j]);
			printf("%lld\n", ans%P);
		}

		if(op == 3) {
			// 3. 区间取min
			scanf("%lld%lld", &l, &r);
			ll ans = v[l];
			for(ll j = l ; j <= r ; ++ j) ans = min(ans, v[j]);
			printf("%lld\n", ans%P);
		}

		if(op == 4) {
			// 4. 插入一段区间
            ll k,tmp,pos;
			scanf("%lld%lld",&k,&pos);
            for(ll j=1;j<=k;j++)
                scanf("%lld",&tmp),
                v.insert(v.begin()+pos+j,tmp);
		}

		if(op == 5) {
			// 5. 删除一段区间
			scanf("%lld%lld", &l, &r);
			vector<ll> tmp; tmp.clear();
			for(ll j = 1 ; j < v.size() ; ++ j) if(j < l || j > r) tmp.push_back(v[j]);
			v.clear();
			v.push_back(-1);
			for(ll j = 0 ; j < tmp.size() ; ++ j) v.push_back(tmp[j]);
		}

		if(op == 6) {
			// 6. 求一个区间的最大子段和
			scanf("%lld%lld", &l, &r);
			for(ll j=l;j<=r;j++)
				tmp[j-l+1]=v[j];
			printf("%lld\n",MaxSum(tmp,r-l+1)%P);
		}

		if(op == 7) {
			// 7. 将一段整体乘一个数
			scanf("%lld%lld%lld", &l, &r, &val);
			for(ll j = l ; j <= r ; ++ j) (v[j] *= val) %= P;
		}

		if(op == 8) {
			// 8. 区间求和
			scanf("%lld%lld", &l, &r);
			ll ans = 0;
			for(ll j = l ; j <= r ; ++ j) (ans += v[j]) %= P;
			printf("%lld\n", ans%P);
		}

		if(op == 9) {
			// 9. 区间求积
			scanf("%lld%lld", &l, &r);
			ll ans = 1;
			for(ll j = l ; j <= r ; ++ j) (ans *= v[j]) %= P;
			printf("%lld\n", ans%P);
		}

        if(op==10) for(ll j=1;j<v.size();j++) printf("%lld ",v[j] % P);

        //puts("");
	}
}
