using System;
using Gtk;
using SalsaMusicalityGUI;

public partial class MainWindow : Gtk.Window
{
    private bool IsPlaying = false;
    //private Button cowbellButton;

    public MainWindow() : base(Gtk.WindowType.Toplevel)
    {
        Build();
        SoundLibraryInterface.SetBeatsPerMinute((uint)bpmSlider.Value);
        SoundLibraryInterface.SetMasterVolume((float)masterVolumeSlider.Value);

        Image claveImg = new Image(Gdk.Pixbuf.LoadFromResource("SalsaMusicalityGUI.claves.jpg"));
        claveImg.Pixbuf = claveImg.Pixbuf.ScaleSimple(40, 40, Gdk.InterpType.Bilinear);

        this.claveButton.Image = claveImg;

        Image cowbellImg = new Image(Gdk.Pixbuf.LoadFromResource("SalsaMusicalityGUI.cowbell.jpg"));
        cowbellImg.Pixbuf = cowbellImg.Pixbuf.ScaleSimple(40, 40, Gdk.InterpType.Bilinear);

        this.cowbellButton.Image = cowbellImg;

        Image bongosImg = new Image(Gdk.Pixbuf.LoadFromResource("SalsaMusicalityGUI.bongos.jpg"));
        bongosImg.Pixbuf = bongosImg.Pixbuf.ScaleSimple(40, 40, Gdk.InterpType.Bilinear);

        this.bongosButton.Image = bongosImg;
    }

    protected void OnDeleteEvent(object sender, DeleteEventArgs a)
    {
        Application.Quit();
        a.RetVal = true;
    }

    protected void OnBpmSliderValueChanged(object sender, EventArgs e)
    {
        Range rng = sender as Range;

        SalsaMusicalityGUI.SoundLibraryInterface.SetBeatsPerMinute((uint)rng.Value);
    }

    protected void OnMasterVolumeSliderChanged(object sender, EventArgs e)
    {
        Range rng = sender as Range;

        SalsaMusicalityGUI.SoundLibraryInterface.SetMasterVolume((float)rng.Value);
    }

    protected void OnPlaybackButtonClicked(object sender, EventArgs e)
    {
        if ( !IsPlaying)
        {
            IsPlaying = true;
            SoundLibraryInterface.BeginPlayback();
        }
    }

    protected void OnBongosButtonClicked(object sender, EventArgs e)
    {
        Button tmpButton = sender as Button;
        bool isEnabled =
            SoundLibraryInterface.IsInstrumentEnabled((uint)INSTRUMENTS_TYPE.INSTRUMENT_BONGOS);

        tmpButton.ModifyBg(StateType.Normal, new Gdk.Color(255, 1, 1));
        SoundLibraryInterface.SetInstrumentEnabled(
            (uint)INSTRUMENTS_TYPE.INSTRUMENT_BONGOS,
            !isEnabled);
    }

    protected void OnCowbellButtonClicked(object sender, EventArgs e)
    {
        bool isEnabled =
            SoundLibraryInterface.IsInstrumentEnabled((uint)INSTRUMENTS_TYPE.INSTRUMENT_COWBELL);

        SoundLibraryInterface.SetInstrumentEnabled(
            (uint)INSTRUMENTS_TYPE.INSTRUMENT_COWBELL,
            !isEnabled);
    }

    protected void OnClaveButtonClicked(object sender, EventArgs e)
    {
        bool isEnabled =
            SoundLibraryInterface.IsInstrumentEnabled((uint)INSTRUMENTS_TYPE.INSTRUMENT_CLAVE);

        SoundLibraryInterface.SetInstrumentEnabled(
            (uint)INSTRUMENTS_TYPE.INSTRUMENT_CLAVE,
            !isEnabled);
    }
}
