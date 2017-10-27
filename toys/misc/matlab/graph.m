
% g = [0,1,0,0; 
%      0,0,0,1; 
%      0,0,0,0; 
%      1,0,1,0];
% 
% tail = head = 1;
% queue = [];
% queue(head++) = 1;
% for k = 1:1:4 % num intermediate vertices
%     queue(tail++) = k;
%     for i = 1:1:4 % source vertex (scan row)
%         for j = 1:1:4 % dest vertex (scan col)
%             fprintf('%d, %d, %d\n', i, j, k);
%             x=g(i,j);
%         end
%     end
%     %x = queue(head);
%     %queue(head++) = [];
% end
% queue


%g = [0,1,0,0; 
%     0,0,0,1; 
%     0,0,0,0; 
%     1,0,1,0];
%
%tail = head = 1;
%queue = [];
%searched = [];
%queue(tail++) = 1;
%while length(queue)
%    item = queue(head++);
%    if searched(item) == 0
%        queue(tail++) = item
%        append(searched, item);
%    end
%end


%
% def bfs(g, start):
%     search_queue = deque()
%     search_queue += g[start]
%     searched = []
%     while search_queue:
%         item = search_queue.popleft()
%         if not item in searched:
%             if len(item):
%                 print "item {}".format(item)
%                 search_queue += g[item]
%                 searched.append(item)

