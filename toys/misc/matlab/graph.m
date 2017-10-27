

% square connection matrix
g = [ 1, 1, 1, 1, 0, 0;
      0, 1, 0, 0, 0, 0;
      0, 0, 1, 0, 1, 1;
      0, 0, 0, 1, 0, 0;
      0, 0, 0, 0, 1, 0;
      0, 0, 0, 0, 0, 1];
n_verts = 6;
start = 1;

global parent  = [];
global visited = [];
function bfs(start, nverts, graph)
    global parent  = [];
    global visited = [];
    ring    = [];
    head = tail = 1;
    for i = 1:1:6
        parent(i) = -1;
        visited(i) = 0;
    end
    visited(start) = 1;
    ring(tail++) = start;
    while (tail != head)
        v = ring(head++);
        fprintf('v: %d\n', v);
        for i = 1:1:nverts
            if (graph(v,i) == 1 && visited(i) == 0)
                fprintf('adding vert %d\n', i);
                ring(tail++) = i;
                visited(i) = 1;
                parent(i) = v;
            end
        end
    end
end

function find_path(first, last, arr)
    if ((first == last) || (last == -1))
        fprintf('start => %02d\n', first);
    else
        find_path(first, arr(last), arr);
        fprintf('         %02d <=\n', last);
    end
end

function reachable(nverts, start, visited_arr)
    fprintf('\n The vertices which are reachable from %d are:\n\n', start); 
    for i = 1:1:nverts
        if (visited_arr(i) != 0)
            fprintf('%d\t',i);
        end
    end
    fprintf('\n');
end

bfs(start, n_verts, g);
reachable(n_verts, start, visited);
find_path(1, 4, parent);

