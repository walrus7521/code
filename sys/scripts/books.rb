#!/usr/bin/ruby

class Entry
    attr :ckno, true
    attr :date, true
    attr :desc, true
end

checkbook = Hash.new
entry = Hash.new
index = 0
while line = gets do
    if line =~ /#/
        #puts "wusup\n"
    else
        #puts line
        e = Entry.new
        array = line.split(/,/)
        ckno = array[0].to_i
        date = array[1]
        desc = array[2]
        #puts array[0], array[1]
        entry.clear
        #e.set_ckno(array[0])
        #e.set_date(array[1])
        e.ckno = array[0]
        e.date = array[1]
        e.desc = array[2]
        #record = { "ckno" => ckno, "date" => date, "desc" => desc }
        entry = { ckno => e } # use the check no as the key
        checkbook.merge! entry
        #printf("%d\n", ckno)
        index = index + 1
    end
end

checkbook.each {
    #|k,v| puts "key: #{k} value: #{v} #{v.ckno} #{v.date} #{v.desc}"
    |k,v| puts "#{k} #{v.date} #{v.desc}"
        
}


