class BST
{
    public:
        inline void insert(int val)
        {
            int last=-1,cur=root;
            while(cur)
            {
                if(BST[cur].val==val) {BST[cur].num++;return;}
                last=cur;
                if(val<BST[cur].val) cur=BST[cur].l;
                else if(val>BST[cur].val) cur=BST[cur].r;
            }
            BST[++cnt].val=val;BST[cnt].num=1;
            if(val<BST[last].val) BST[last].l=cnt;
            else BST[last].r=cnt;
            BST[cnt].fa=last;
        }
        int search(int val)
        {
            int cur=root;
            while(cur)
            {
                if(BST[cur].val==val) return cur;
                else if(val<BST[cur].val) cur=BST[cur].l;
                else cur=BST[cur].r;
            }
            return -1;
        }
        void del(int val)
        {
            int pos=search(val);
            if(pos==-1) return;
            BST[pos].num--;
            if(BST[pos].num) return;
            if(!BST[pos].l&&!BST[pos].r)
            {
                if(val<BST[BST[pos].fa].val) BST[BST[pos].fa].l=0;
                else BST[BST[pos].fa].r=0;
                return;
            }
            if(!BST[pos].l)
            {
                if(val<BST[BST[pos].fa].val) BST[BST[pos].fa].l=BST[pos].r;
                else BST[BST[pos].fa].r=BST[pos].r;
                BST[BST[pos].r].fa=BST[pos].fa;
                return;
            }else if(!BST[pos].r)
            {
                if(val<BST[BST[pos].fa].val) BST[BST[pos].fa].l=BST[pos].l;
                else BST[BST[pos].fa].r=BST[pos].l;
                BST[BST[pos].l].fa=BST[pos].fa;
                return;
            }else
            {
                int cur=BST[pos].r,last;
                while(cur)
                    last=cur,cur=BST[cur].l;
                del_pos_only(last);
                if(val<BST[BST[pos].fa].val) BST[BST[pos].fa].l=last;
                    else BST[BST[pos].fa].r=last;
                BST[last].fa=BST[pos].fa;
            }
        }
    private:
        struct node{
            int l,r,num,val;
            int fa;
        }BST[100000];
        int cnt=0;
        const int root=1;
        void del_pos_only(int pos)
        {
            int val=BST[pos].val;
            if(!BST[pos].l&&!BST[pos].r)
            {
                if(val<BST[BST[pos].fa].val) BST[BST[pos].fa].l=0;
                else BST[BST[pos].fa].r=0;
                return;
            }
            if(!BST[pos].l)
            {
                if(val<BST[BST[pos].fa].val) BST[BST[pos].fa].l=BST[pos].r;
                else BST[BST[pos].fa].r=BST[pos].r;
                return;
            }else if(!BST[pos].r)
            {
                if(val<BST[BST[pos].fa].val) BST[BST[pos].fa].l=BST[pos].l;
                else BST[BST[pos].fa].r=BST[pos].l;
                return;
            }
        }
};
