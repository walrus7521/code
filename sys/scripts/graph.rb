#!/usr/bin/ruby

class Graph
    attr :nvertices, true
    attr :nedges, true
    class << self
        def read_graph
            line = gets
            array = line.split(/ /)
            nvertices = array[0].to_i
            nedges = array[1].to_i
            puts nvertices, nedges
            x = 0
            y = 0
            while line = gets do
                array = line.split(/ /)
               x = array[0].to_i
               y = array[1].to_i
               printf("%d, %d\n", x, y)
            end
        end

        def greeting
            print 'hello'
        end
    end
end

#graph = Graph.new
Graph.read_graph
#m.call
#graph.method(:read_graph)

#checkbook.each {
#    #|k,v| puts "key: #{k} value: #{v} #{v.ckno} #{v.date} #{v.desc}"
#    |k,v| puts "#{k} #{v.date} #{v.desc}"
#        
#}


