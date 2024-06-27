18 additions and 0 deletions.
  18 changes: 18 additions & 0 deletions18  
drivers/gpu/drm/msm/dsi-staging/dsi_panel.c
Copied!
Original file line number	Diff line number	Diff line change
@@ -1035,6 +1035,15 @@ static int dsi_panel_bl_unregister(struct dsi_panel *panel)
	return rc;
}

static bool in_recovery;

static int __init boot_mode_setup(char *value)
{
	in_recovery = !strcmp(value, "1");
	return 1;
}
__setup("androidboot.force_normal_boot=", boot_mode_setup);

static int dsi_panel_parse_timing(struct dsi_mode_info *mode,
				  struct dsi_parser_utils *utils)
{
@@ -1075,6 +1084,9 @@ static int dsi_panel_parse_timing(struct dsi_mode_info *mode,
	rc = utils->read_u32(utils->data,
				"qcom,mdss-dsi-panel-framerate",
				&mode->refresh_rate);
        if(!in_recovery)
		mode->refresh_rate = 104;

	if (rc) {
		pr_err("failed to read qcom,mdss-dsi-panel-framerate, rc=%d\n",
		       rc);
@@ -1627,6 +1639,12 @@ static int dsi_panel_parse_dfps_caps(struct dsi_panel *panel)
	const char *type;
	u32 i;

        if(!in_recovery){
		dfps_caps->dfps_support = false;
		return rc;
	}


	supported = utils->read_bool(utils->data,
			"qcom,mdss-dsi-pan-enable-dynamic-fps");
