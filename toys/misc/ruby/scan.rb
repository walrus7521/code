#!/usr/bin/env ruby

require 'colorize'
# gem install colorize
# https://stackoverflow.com/questions/1489183/colorized-ruby-output

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
#       puts "match: " +  matches[i]
#       printf "match[%d] = %s\n", i, matches[i]
        str = sprintf "match[%d] = %s", i, matches[i]
        puts str.yellow
    end

    puts "error: invalid regex".red
    puts "  now I'm feeling blue".blue
    puts "  and a little envious".yellow

end

