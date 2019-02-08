#!/usr/bin/env ruby


#lines = STDIN.read
#while line = gets.chomp
#    puts line

STDIN.each_line do |line|
    #puts "dude: " + line
    matches = line.match(/(cool).*(crap)/)

#   len = matches.length
#   puts "matches: " + len.to_s
#   len.times do |n|
#       puts "match: " +  matches[n]
#   end

    limit = matches.length;
    puts "matches: " + limit.to_s
    for i in 1..limit-1
        puts "match: " +  matches[i]
    end

end
    
