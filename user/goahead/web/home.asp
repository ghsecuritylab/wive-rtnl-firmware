<HTML>
<!-- Copyright (c) Go Ahead Software Inc., 1994-2000. All Rights Reserved. -->
<!-- Copyright (c) Ralink (2004-2010) Tech Inc. All Rights Reserved. -->
<!-- Copyright (c) Wive project (2010-2011). All Rights Reserved. -->
<HEAD>
<TITLE>Wive-RTNL</TITLE>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Cache-Control" content="no-store, no-cache, must-revalidate, post-check=0, pre-check=0">
<meta http-equiv="Pragma" content="no-cache">

<script type="text/javascript" src="/js/ajax.js"></script>

<script language="JavaScript" type="text/javascript">
function initLanguage()
{
	var lang = "<% getCfgGeneral(1, "Language"); %>";
	if (lang=="")
		lang = "en";
	var cook = "en";
	var lang_en = "<% getLangBuilt("en"); %>";

	if (document.cookie.length > 0) {
		var s = document.cookie.indexOf("language=");
		var e = document.cookie.indexOf(";", s);
		if (s != -1) {
			if (e == -1)
				cook = document.cookie.substring(s+9);
			else
				cook = document.cookie.substring(s+9, e);
		}
	}

	if (lang == "en") {
		document.cookie="language=en; path=/";
		if (cook != lang)
			window.location.reload();
	} else {
		document.cookie="language=en; path=/";
		lang_en == "1";
		window.location.reload();
	}
}

function onInit()
{
	initLanguage();
}

</script>
</HEAD>
<FRAMESET id="homeFrameset" ROWS="40,1*" COLS="*" BORDER="0" FRAMESPACING="0" FRAMEBORDER="NO" onLoad="onInit()">

  <FRAME SRC="title.htm" NAME="title" FRAMEBORDER="NO" SCROLLING="NO" MARGINWIDTH="0" MARGINHEIGHT="0">

  <FRAMESET id="homeMenuFrameset" COLS="200,1*">

    <FRAME SRC="treeapp.asp" NAME="menu" MARGINWIDTH="0" MARGINHEIGHT="0" scrolling="AUTO" FRAMEBORDER="NO" >

    <FRAME SRC="overview.asp" NAME="view" SCROLLING="AUTO" MARGINWIDTH="0" TOPMARGIN="0" MARGINHEIGHT="0" FRAMEBORDER="NO">
  </FRAMESET>
</FRAMESET>

<NOFRAMES>
<BODY BGCOLOR="#FFFFFF">
</BODY>
</NOFRAMES>

</HTML>
