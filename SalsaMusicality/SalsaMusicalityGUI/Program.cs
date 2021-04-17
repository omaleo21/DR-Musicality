using System;
using Gtk;

namespace SalsaMusicalityGUI
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Application.Init();
            int retval = SoundLibraryInterface.InitializeSoundLibrary("../SoundFonts/");
            if ( retval != 0)
            {
                return;
            }
            MainWindow win = new MainWindow();
            win.Show();
            Application.Run();

            SoundLibraryInterface.FreeSoundLibrary();
        }
    }
}
