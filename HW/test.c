        Node *last_head_route = copyLinkedList(head_route);
        //Prune the route
        //Prune calc distance
        int max_distance[numNodes];//Record max distance
        int max_distance_index_lowerbound[numNodes];//Record index
        int max_distance_index_upperbound[numNodes];
        for(int i=0;i<numNodes;i++){
            int lowerbound=i;
            int upperbound=newPath[i];
            int lowerbound_index=-1;
            int upperbound_index=-1;
            
            //Find lowerbound index in route
            int bound_index_count=0;
            temp=head_route;

            while (temp!=NULL)
            {
                if(findElement(temp->vec,lowerbound)!=-1){
                    lowerbound_index=bound_index_count;
                    break;
                }
                bound_index_count++;
                temp=temp->next;
            }
        

            //Find upperbound index in route
            bound_index_count=0;
            temp=head_route;
            while (temp!=NULL)
            {   
                //If newPath point to NULL
                if(upperbound==-1){
                    upperbound_index=lowerbound_index;
                    break;
                }
                else{
                    if(findElement(temp->vec,upperbound)!=-1){
                        upperbound_index=bound_index_count;
                        break;
                    }
                }

                bound_index_count++;
                temp=temp->next;
            }

            //Calc max distance or not
            if((upperbound_index-lowerbound_index)>max_distance){
                max_distance=upperbound_index-lowerbound_index;
                max_distance_index_lowerbound=lowerbound_index;
                max_distance_index_upperbound=upperbound_index;
            }