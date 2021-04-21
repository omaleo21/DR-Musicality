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

        AssignImageToButton(ref claveButton, "SalsaMusicalityGUI.claves.jpg");
        AssignImageToButton(ref cowbellButton, "SalsaMusicalityGUI.cowbell.jpg");
        AssignImageToButton(ref bongosButton, "SalsaMusicalityGUI.bongos.jpg");
        AssignImageToButton(ref congasButton, "SalsaMusicalityGUI.congas.jpg");

        // Populate the clave rhythms box
        for (CLAVE_RHYTHMS_TYPE i = 0; i < CLAVE_RHYTHMS_TYPE.NUM_CLAVE_RHYTHMS; i++)
        {
            claveRhythmsBox.InsertText((int)i, CSetup.GetStr_ClaveRhythmsType(i));
        }

        Gtk.TreeIter iter;
        claveRhythmsBox.Model.IterNthChild(out iter, (int)CLAVE_RHYTHMS_TYPE.CLA_SON_2_3);
        claveRhythmsBox.SetActiveIter(iter);

        // Populate the conga rhythms box
        for (CONGA_RHYTHMS_TYPE i = 0; i < CONGA_RHYTHMS_TYPE.NUM_CONGA_RHYTHMS; i++)
        {
            congasRhythmsBox.InsertText((int)i, CSetup.GetStr_CongaRhythmsType(i));
        }

        congasRhythmsBox.Model.IterNthChild(out iter, (int)CONGA_RHYTHMS_TYPE.CON_BASIC_OFFBEAT);
        congasRhythmsBox.SetActiveIter(iter);

        // Populate the cowbell rhythms box
        for (COWBELL_RHYTHMS_TYPE i = 0; i < COWBELL_RHYTHMS_TYPE.NUM_COWBELL_RHYTHMS; i++)
        {
            cowbellRhythmsBox.InsertText((int)i, CSetup.GetStr_CowbellRhythmsType(i));
        }

        cowbellRhythmsBox.Model.IterNthChild(out iter, (int)COWBELL_RHYTHMS_TYPE.COW_DOWN_BEATS);
        cowbellRhythmsBox.SetActiveIter(iter);

        // Populate the bongos rhythms box
        for (BONGO_RHYTHMS_TYPE i = 0; i < BONGO_RHYTHMS_TYPE.NUM_BONGO_RHYTHMS; i++)
        {
            bongosRhythmsBox.InsertText((int)i, CSetup.GetStr_BongosRhythmsType(i));
        }

        bongosRhythmsBox.Model.IterNthChild(out iter, (int)BONGO_RHYTHMS_TYPE.BON_MARTILLO);
        bongosRhythmsBox.SetActiveIter(iter);
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

    protected void OnClaveRhythmsBoxChanged(object sender, EventArgs e)
    {
        ComboBox box = sender as ComboBox;
        CLAVE_RHYTHMS_TYPE rhythmType =
            CSetup.GetEnumFromStr_ClaveRhythmsType(box.ActiveText);

        SoundLibraryInterface.SetInstrumentRhythm(
            (uint)INSTRUMENTS_TYPE.INSTRUMENT_CLAVE,
            (short)rhythmType );
    }

    protected void OnCowbellRhythmsBoxChanged(object sender, EventArgs e)
    {
        ComboBox box = sender as ComboBox;
        COWBELL_RHYTHMS_TYPE rhythmType =
            CSetup.GetEnumFromStr_CowbellRhythmsType(box.ActiveText);

        SoundLibraryInterface.SetInstrumentRhythm(
            (uint)INSTRUMENTS_TYPE.INSTRUMENT_COWBELL,
            (short)rhythmType);
    }

    protected void OnBongosRhythmsBoxChanged(object sender, EventArgs e)
    {
        ComboBox box = sender as ComboBox;
        BONGO_RHYTHMS_TYPE rhythmType =
            CSetup.GetEnumFromStr_BongosRhythmsType(box.ActiveText);

        SoundLibraryInterface.SetInstrumentRhythm(
            (uint)INSTRUMENTS_TYPE.INSTRUMENT_BONGOS,
            (short)rhythmType);
    }

    protected void AssignImageToButton(ref Button iButton, string iImagePath)
    {
        Image img = new Image(Gdk.Pixbuf.LoadFromResource(iImagePath));
        img.Pixbuf = img.Pixbuf.ScaleSimple(40, 40, Gdk.InterpType.Bilinear);

        iButton.Image = img;
    }

    protected void OnCongasButtonClicked(object sender, EventArgs e)
    {
        bool isEnabled =
            SoundLibraryInterface.IsInstrumentEnabled((uint)INSTRUMENTS_TYPE.INSTRUMENT_CONGAS);

        SoundLibraryInterface.SetInstrumentEnabled(
            (uint)INSTRUMENTS_TYPE.INSTRUMENT_CONGAS,
            !isEnabled);
    }

    protected void OnCongasRhythmsBoxChanged(object sender, EventArgs e)
    {
        ComboBox box = sender as ComboBox;
        CONGA_RHYTHMS_TYPE rhythmType =
            CSetup.GetEnumFromStr_CongaRhythmsType(box.ActiveText);

        SoundLibraryInterface.SetInstrumentRhythm(
            (uint)INSTRUMENTS_TYPE.INSTRUMENT_CONGAS,
            (short)rhythmType);
    }
}
