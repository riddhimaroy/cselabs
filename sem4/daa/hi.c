void findmincost(int assigned[], int used[], int person, int curr_cost)
{
    if(person==N)
    {
        if(min_cost>curr_cost)
            curr_cost=min_cost;
            return;
    }

    for(int i=0; i<N; i++)
    {
        if(used[i]==0)
        {
            used[i]=1;
            assigned[person] = i;
            findmincost(assigned, used, person+1, curr_cost+jobs[person][i]);
        }
    }
}