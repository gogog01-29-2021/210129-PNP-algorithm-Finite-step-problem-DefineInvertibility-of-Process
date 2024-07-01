if(src=dst) return true;
if(visited.has(src)) return false;

visited.add(src);

for(let neightbor of graph[src]){
    if(hasPath(graph,neighbor,dst,visited)==true){
        return true;
        }
}
return false;
};

const buildGraph=(edges)=>{
    const graph={};
    for(let edge of edges){
        if(!(a in graph)) graph[a]=[];
        if(!(b in graph)) graph[b]=[];
        graph[a].push(b);
        graph[b].push(a);
        
        }

return graph;


    };
