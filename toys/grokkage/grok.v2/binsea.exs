IO.puts "binary search"

list = [3,1,2]
IO.inspect list

slist = Enum.sort(list)
IO.inspect slist

len = length(slist)
IO.inspect len

for item <- slist do
    IO.inspect item
end



