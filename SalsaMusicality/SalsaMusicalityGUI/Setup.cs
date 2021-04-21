using System;
namespace SalsaMusicalityGUI
{
    internal static class CSetup
    {
        internal static string GetStr_InstrumentType(INSTRUMENTS_TYPE iType)
        {
            switch (iType)
            {
                case INSTRUMENTS_TYPE.INSTRUMENT_CONGAS:
                    return "Congas";
                case INSTRUMENTS_TYPE.INSTRUMENT_CLAVE:
                    return "Clave";
                case INSTRUMENTS_TYPE.INSTRUMENT_COWBELL:
                    return "Cowbell";
                case INSTRUMENTS_TYPE.INSTRUMENT_BONGOS:
                    return "Bongos";
                default:
                    return "None";
            }
        }

        internal static INSTRUMENTS_TYPE GetEnumFromStr_InstrumentType(string iType)
        {
            if ( string.Compare(iType, "Congas") == 0)
            {
                return INSTRUMENTS_TYPE.INSTRUMENT_CONGAS;
            }
            else if (string.Compare(iType, "Clave") == 0)
            {
                return INSTRUMENTS_TYPE.INSTRUMENT_CLAVE;
            }
            else if (string.Compare(iType, "Cowbell") == 0)
            {
                return INSTRUMENTS_TYPE.INSTRUMENT_COWBELL;
            }
            else if (string.Compare(iType, "Bongos") == 0)
            {
                return INSTRUMENTS_TYPE.INSTRUMENT_BONGOS;
            }
            else
            {
                return INSTRUMENTS_TYPE.NUM_INSTRUMENTS;
            }
        }

        internal static string GetStr_BongosRhythmsType(BONGO_RHYTHMS_TYPE iType)
        {
            switch (iType)
            {
                case BONGO_RHYTHMS_TYPE.BON_ALL_BEATS:
                    return "All Beats";
                case BONGO_RHYTHMS_TYPE.BON_MARTILLO:
                    return "Martillo";
                default:
                    return "None";
            }
        }

        internal static BONGO_RHYTHMS_TYPE GetEnumFromStr_BongosRhythmsType(string iType)
        {
            if (string.Compare(iType, "All Beats") == 0)
            {
                return BONGO_RHYTHMS_TYPE.BON_ALL_BEATS;
            }
            else if (string.Compare(iType, "Martillo") == 0)
            {
                return BONGO_RHYTHMS_TYPE.BON_MARTILLO;
            }
            else
            {
                return BONGO_RHYTHMS_TYPE.NUM_BONGO_RHYTHMS;
            }
        }

        internal static string GetStr_ClaveRhythmsType(CLAVE_RHYTHMS_TYPE iType)
        {
            switch (iType)
            {
                case CLAVE_RHYTHMS_TYPE.CLA_RUMBA_2_3:
                    return "Rumba 2/3";
                case CLAVE_RHYTHMS_TYPE.CLA_RUMBA_3_2:
                    return "Rumba 3/2";
                case CLAVE_RHYTHMS_TYPE.CLA_SON_2_3:
                    return "Son 2/3";
                case CLAVE_RHYTHMS_TYPE.CLA_SON_3_2:
                    return "Son 3/2";
                default:
                    return "None";
            }
        }

        internal static CLAVE_RHYTHMS_TYPE GetEnumFromStr_ClaveRhythmsType(string iType)
        {
            if (string.Compare(iType, "Rumba 2/3") == 0)
            {
                return CLAVE_RHYTHMS_TYPE.CLA_RUMBA_2_3;
            }
            else if (string.Compare(iType, "Rumba 3/2") == 0)
            {
                return CLAVE_RHYTHMS_TYPE.CLA_RUMBA_3_2;
            }
            else if (string.Compare(iType, "Son 2/3") == 0)
            {
                return CLAVE_RHYTHMS_TYPE.CLA_SON_2_3;
            }
            else if (string.Compare(iType, "Son 3/2") == 0)
            {
                return CLAVE_RHYTHMS_TYPE.CLA_SON_3_2;
            }
            else
            {
                return CLAVE_RHYTHMS_TYPE.NUM_CLAVE_RHYTHMS;
            }
        }

        internal static string GetStr_CongaRhythmsType(CONGA_RHYTHMS_TYPE iType)
        {
            switch (iType)
            {
                case CONGA_RHYTHMS_TYPE.CON_BASIC_OFFBEAT:
                    return "Basic Offbeat";
                case CONGA_RHYTHMS_TYPE.CON_BASIC_ENDBEAT:
                    return "Basic Endbeat";
                case CONGA_RHYTHMS_TYPE.CON_CLAVE_ALIGNED:
                    return "Clave Aligned";
                default:
                    return "None";
            }
        }

        internal static CONGA_RHYTHMS_TYPE GetEnumFromStr_CongaRhythmsType(string iType)
        {
            if (string.Compare(iType, "Basic Offbeat") == 0)
            {
                return CONGA_RHYTHMS_TYPE.CON_BASIC_OFFBEAT;
            }
            else if (string.Compare(iType, "Basic Endbeat") == 0)
            {
                return CONGA_RHYTHMS_TYPE.CON_BASIC_ENDBEAT;
            }
            else if (string.Compare(iType, "Clave Aligned") == 0)
            {
                return CONGA_RHYTHMS_TYPE.CON_CLAVE_ALIGNED;
            }
            else
            {
                return CONGA_RHYTHMS_TYPE.NUM_CONGA_RHYTHMS;
            }
        }

        internal static string GetStr_CowbellRhythmsType(COWBELL_RHYTHMS_TYPE iType)
        {
            switch (iType)
            {
                case COWBELL_RHYTHMS_TYPE.COW_ALL_BEATS:
                    return "All Beats";
                case COWBELL_RHYTHMS_TYPE.COW_CLAVE_ALIGNED:
                    return "Clave Aligned";
                case COWBELL_RHYTHMS_TYPE.COW_DOWN_BEATS:
                    return "Down Beats";
                default:
                    return "None";
            }
        }

        internal static COWBELL_RHYTHMS_TYPE GetEnumFromStr_CowbellRhythmsType(string iType)
        {
            if (string.Compare(iType, "All Beats") == 0)
            {
                return COWBELL_RHYTHMS_TYPE.COW_ALL_BEATS;
            }
            else if (string.Compare(iType, "Clave Aligned") == 0)
            {
                return COWBELL_RHYTHMS_TYPE.COW_CLAVE_ALIGNED;
            }
            else if (string.Compare(iType, "Down Beats") == 0)
            {
                return COWBELL_RHYTHMS_TYPE.COW_DOWN_BEATS;
            }
            else
            {
                return COWBELL_RHYTHMS_TYPE.NUM_COWBELL_RHYTHMS;
            }
        }
    }
}
