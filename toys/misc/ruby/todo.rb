#!/usr/bin/ruby

    
class TodoList < Array
    def self.load(file)
        # read the file, create a list, create items, add them to the list, return the list
        list = TodoList.new
        File.read(file).each_line do |line|
            list << line.chomp
        end
 
        list
    end
 
    def add(todo)
        if todo.is_a?(TodoItem)
            push(todo)
        else
            push(TodoItem.new(todo))
        end
    end
 
    alias_method :<<, :add
    
    def mark_done(id)
        self[id - 1].done = true
    end
 
    def write(file)
        File.open(file, 'w') do |f|
            f.write(reject {|item| item.done?}.join("\n"))
        end
    end
end
 
class TodoItem
    # provide reader and setter for name and state
    attr_accessor :name, :done
    alias_method :done?, :done
 
    def initialize(name)
        # store name
        # set state to undone
        @name = name
        @done = false
    end
 
    def to_s
        @name   
    end
end
 
class CommandLineInterface
    def initialize
        @list = TodoList.load("todo.td")    
    end
 
    def done
        @list.done ARGV[1]
    end
 
    def add
        @list << ARGV[1..-1].join(" ")
    end
 
    def write
        @list.write("todo.td")
    end
 
    def list
        @list.each_with_index do |line, index|
            puts "##{index + 1} - #{line.name.capitalize}"
        end
    end
end
 
cli = CommandLineInterface.new

prompt = "> "
print prompt

while true # loop forever
    user_input = gets.chomp # get user input
    case user_input
        when "1"
            puts "First response"
            print prompt
        when "list"
            puts "list"
            cli.list()
            print prompt
        when "help"
            puts "add, done, write, list"
            print prompt
        when "quit"
            puts "quit"
            break
        else
            print prompt # print the prompt, so the user knows to re-enter input
    end
end

#cli.send ARGV[0]
#cli.write

#the library will be used like this:
list = TodoList.load("todo.td")
list[0].done = true
list.add TodoItem.new("another cool item, oh crap")
list.write("todo.td")

