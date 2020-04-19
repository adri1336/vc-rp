#include <YSI\y_hooks>

hook OnScriptInit()
{
    ToggleTextDrawLayerLabels(LAYER_MSELECTION, false);
    ToggleTextDrawLayerLabels(LAYER_LOADSCREEN, false);
    ToggleTextDrawLayerLabels(LAYER_FADESCREEN, false);
    ToggleTextDrawLayerLabels(LAYER_GPS, false);
    ToggleTextDrawLayerLabels(LAYER_BUSINESS_DIALOG, false);
    ToggleTextDrawLayerLabels(LAYER_ATM, false);
    ToggleTextDrawLayerLabels(LAYER_TUTORIAL, false);
    SetTextdrawLayerAlwaysOn(LAYER_TUTORIAL, true);
    return 1;
}