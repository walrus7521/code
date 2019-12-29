#!/usr/bin/ruby

require "tk"
require 'tkextlib/bwidget'

root = TkRoot.new
root.title = "PUMA"
$var

f1 = TkFrame.new {
    relief 'sunken'
    borderwidth 3
#background "red"
    padx 15
    pady 20
   pack('side' => 'left')
}
f2 = TkFrame.new {
    relief 'groove'
    borderwidth 1
#    background "yellow"
    padx 10
    pady 10
    pack('side' => 'right')
}
f3 = TkFrame.new {
    relief 'groove'
    borderwidth 1
#    background "blue"
    padx 10
    pady 50
    pack('side' => 'bottom')
}


progressBar = Tk::BWidget::ProgressBar.new(root)
variable = TkVariable.new
progressBar.variable = variable
$var = 11
variable.value = $var
progressBar.maximum = 100
progressBar.place('height' => 25,
                  'width'  => 100,
                  'x'      => 10,
                  'y'      => 10)

combobox = Tk::BWidget::ComboBox.new(root)
combobox.values = [1, 2, 3, 4]
combobox.place('height' => 25,
               'width'  => 100,
               'x'      => 20,
               'y'      => 50)


TkButton.new(f1) {
    text 'Button1'
    command {
        print "push button1!!\n"
        $var += 4
        variable.value = $var
    }
    pack('fill' => 'x')
}
TkButton.new(f1) {
    text 'Button2'
    command {
        print "push button2!!\n"
    }
    pack('fill' => 'x')
}
TkButton.new(f2) {
    text 'Quit'
    command 'exit'
    pack('fill' => 'x')
}


menu_click = Proc.new {
  Tk.messageBox(
    'type'    => "ok",  
    'icon'    => "info",
    'title'   => "Yo wusup!!",
    'message' => "Message"
  )
}

cmd_click = Proc.new {
  Tk.messageBox(
    'type'    => "ok",  
    'icon'    => "info",
    'title'   => "PUMA Script launch..",
    'message' => "Message"
  )
}

file_menu = TkMenu.new(root)
cmd_menu = TkMenu.new(root)

file_menu.add('command',
              'label'     => "New...",
              'command'   => menu_click,
              'underline' => 0)
file_menu.add('command',
              'label'     => "Open...",
              'command'   => menu_click,
              'underline' => 0)
file_menu.add('command',
              'label'     => "Close",
              'command'   => menu_click,
              'underline' => 0)
file_menu.add('separator')
file_menu.add('command',
              'label'     => "Save",
              'command'   => menu_click,
              'underline' => 0)
file_menu.add('command',
              'label'     => "Save As...",
              'command'   => menu_click,
              'underline' => 5)
file_menu.add('separator')
file_menu.add('command',
              'label'     => "Exit",
              'command'   => 'exit',
              'underline' => 3)

cmd_menu.add('command',
             'label'      => "Exec",
             'command'    => cmd_click,
             'underline'  => 0)

menu_bar = TkMenu.new
menu_bar.add('cascade',
             'menu'  => file_menu,
             'label' => "File")
menu_bar.add('cascade',
             'menu'  => cmd_menu,
             'label' => "Commands")

root.menu(menu_bar)

Tk.mainloop

