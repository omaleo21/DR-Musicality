
// This file has been generated by the GUI designer. Do not modify.
namespace Stetic
{
	internal class Gui
	{
		private static bool initialized;

		internal static void Initialize(Gtk.Widget iconRenderer)
		{
			if ((Stetic.Gui.initialized == false))
			{
				Stetic.Gui.initialized = true;
				global::Gtk.IconFactory w1 = new global::Gtk.IconFactory();
				global::Gtk.IconSet w2 = new global::Gtk.IconSet(new global::Gdk.Pixbuf(global::System.IO.Path.Combine(global::System.AppDomain.CurrentDomain.BaseDirectory, "./claves.jpg")));
				w1.Add("Claves", w2);
				w1.AddDefault();
			}
		}
	}

	internal class ActionGroups
	{
		public static Gtk.ActionGroup GetActionGroup(System.Type type)
		{
			return Stetic.ActionGroups.GetActionGroup(type.FullName);
		}

		public static Gtk.ActionGroup GetActionGroup(string name)
		{
			return null;
		}
	}
}
