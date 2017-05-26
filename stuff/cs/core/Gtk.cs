using Gtk;
using System;

//  mcs gtk.cs -pkg:gtk-sharp-2.0

class Hello
{
    static void Main ()
    {
        Application.Init ();

        Window window = new Window ("Hello Mono World");
        window.Show ();

        Application.Run ();
    }
}
