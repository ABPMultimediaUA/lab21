(function(g){var window=this;var r9=function(a,b,c,d){var e=b.Ib();g.le(a.element,"ytp-suggestion-set",!!e.videoId);var f=b.Wg();d=b.Bc(c,d?d:"mqdefault.jpg");var k=b instanceof g.oC?g.Xk(b.lengthSeconds):null,l=!!f,f=l&&"RD"==g.zE(f).type;c={title:b.title,author:b.author,author_and_views:e.shortViewCount?b.author+" \u2022 "+e.shortViewCount:b.author,watch:g.P("YTP_WATCH_VIDEO_OR_PLAYLIST",{TITLE:b.title},b.title),duration:k,url:b.sj(c),is_list:l,is_mix:f,background:d?"background-image: url("+d+")":""};b instanceof g.CE&&(c.playlist_length=
b.A);a.update(c)},s9=function(a){var b=g.T(a),c=b.experiments.$("video_wall_moving_thumbnails_autoplay"),d=b.experiments.$("video_wall_moving_thumbnails_hover"),c=c||d;
this.B=b.B&&!b.D;b={J:"img",Y:"ytp-videowall-moving-thumbnail",X:{src:"{{moving_thumbnail}}"}};g.R.call(this,{J:"a",Y:"ytp-videowall-still",X:{href:"{{url}}",target:this.B?"_blank":null,"aria-label":"{{watch}}","data-is-list":"{{is_list}}","data-is-mix":"{{is_mix}}"},T:[{J:"div",Y:"ytp-videowall-still-image",X:{style:"{{background}}"}},c?b:null,{J:"span",Y:"ytp-videowall-still-info",T:[{J:"span",Y:"ytp-videowall-still-info-bg",T:[{J:"span",Y:"ytp-videowall-still-info-content",X:g.Gi||g.zc?{style:"will-change: opacity"}:
null,T:[{J:"span",Y:"ytp-videowall-still-info-title",T:["{{title}}"]},{J:"span",Y:"ytp-videowall-still-info-author",T:["{{author_and_views}}"]},{J:"span",Y:"ytp-videowall-still-info-duration",T:["{{duration}}"]}]}]}]},{J:"span",ga:["ytp-videowall-still-listlabel-regular","ytp-videowall-still-listlabel"],T:[{J:"span",Y:"ytp-videowall-still-listlabel-icon"},g.P("YTP_PLAYLIST"),{J:"span",Y:"ytp-videowall-still-listlabel-length",T:[" (",{J:"span",T:["{{playlist_length}}"]},")"]}]},{J:"span",ga:["ytp-videowall-still-listlabel-mix",
"ytp-videowall-still-listlabel"],T:[{J:"span",Y:"ytp-videowall-still-listlabel-mix-icon"},g.P("YTP_MIX"),{J:"span",Y:"ytp-videowall-still-listlabel-length",T:[" (50+)"]}]}]});this.g=a;this.o=null;this.R("click",this.IJ);this.R("keypress",this.JJ);c&&this.S(this.wa["ytp-videowall-moving-thumbnail"],"load",this.LJ);g.T(a).experiments.$("player_interaction_logging")&&(a=a.app.ca,g.kb(a.B,this),b=String(a.F++),this.element.setAttribute("data-visual-id",b),g.Kb(this,(0,g.y)(a.D,a,this)))},t9=function(a){if(5E5<
g.qx(a.g.app.la)){var b=a.o.lj();
b&&a.update({moving_thumbnail:b})}},u9=function(a){g.LE.call(this,a,{J:"div",
ga:["ytp-thumbnail-overlay","ytp-channel-overlay"],T:[{J:"div",Y:"ytp-thumbnail-overlay-image",X:{style:"{{background}}"}},{J:"div",Y:"ytp-thumbnail-overlay-curtain"}]})},v9=function(a){var b=g.T(a).experiments.$("moving_thumbnails_autonav"),c={J:"img",
Y:"ytp-upnext-moving-thumbnail",X:{src:"{{moving_thumbnail}}"}},c={J:"div",Y:"ytp-upnext",X:{"aria-label":"{{watch}}"},T:[{J:"div",Y:"ytp-thumbnail-overlay-image",X:{style:"{{background}}"}},b?c:null,{J:"div",Y:"ytp-thumbnail-overlay-curtain"},{J:"span",Y:"ytp-upnext-top",T:[{J:"span",Y:"ytp-upnext-header",T:[g.P("YTP_PLAYLIST_UP_NEXT")]},{J:"span",Y:"ytp-upnext-title",T:["{{title}}"]},{J:"span",Y:"ytp-upnext-author",T:["{{author}}"]}]},{J:"a",Y:"ytp-upnext-autoplay-icon",X:{href:"{{url}}"},T:[{J:"svg",
X:{height:"100%",version:"1.1",viewBox:"0 0 98 98",width:"100%"},T:[{J:"circle",Y:"ytp-svg-autoplay-circle",X:{cx:"49",cy:"49",fill:"#000","fill-opacity":"0.8",r:"48"}},{J:"circle",Y:"ytp-svg-autoplay-ring",X:{cx:"-49",cy:"49","fill-opacity":"0",r:"46.5",stroke:"#FFFFFF","stroke-dasharray":"293","stroke-dashoffset":"-293","stroke-width":"4",transform:"rotate(-90)"}},{J:"polygon",Y:"ytp-svg-autoplay-triangle",X:{fill:"#fff",points:"32,27 72,49 32,71"}}]}]},{J:"span",Y:"ytp-upnext-bottom",T:[{J:"span",
Y:"ytp-upnext-cancel"},{J:"span",Y:"ytp-upnext-paused",T:[g.P("YTP_AUTOPLAY_PAUSED_2")]}]},{J:"span",Y:"ytp-upnext-close"}]};g.R.call(this,c);this.C=null;var d=this.wa["ytp-upnext-cancel"],c=this.wa["ytp-upnext-close"];this.C=new g.R({J:"button",ga:["ytp-upnext-cancel-button","ytp-button"],X:{tabindex:0,"aria-label":g.P("YTP_AUTOPLAY_CANCEL")},T:[g.P("YTP_CANCEL")]});g.K(this,this.C);this.C.R("click",this.ys,this);this.C.Ea(d);d=new g.R({J:"button",ga:["ytp-upnext-close-button","ytp-button"]});g.K(this,
d);d.R("click",this.ys,this);d.Ea(c);this.g=a;this.H=this.wa["ytp-svg-autoplay-ring"];this.D=this.B=this.o=this.A=null;this.F=new g.ce(this.$i,5E3,this);g.K(this,this.F);this.G=0;this.S(this.wa["ytp-upnext-autoplay-icon"],"click",this.QE);this.ws();this.S(a,"autonavvisibility",this.ws);this.S(a,"mdxnowautoplaying",this.gE);this.S(a,"mdxautoplaycanceled",this.hE);this.S(a,"mdxautoplayupnext",this.IH);b&&this.S(this.wa["ytp-upnext-moving-thumbnail"],"load",this.mL)},w9=function(a,b){a.A=b;
r9(a,b,g.T(a.g),"hqdefault.jpg");g.je(a.element,"ytp-moving-thumbnail-loaded");a.update({moving_thumbnail:"data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7"});5E5<g.qx(a.g.app.la)&&(b=a.A.lj())&&a.update({moving_thumbnail:b})},x9=function(a,b){a.o||(g.cm("a11y-announce",g.P("YTP_PLAYLIST_UP_NEXT")+" "+a.A.title),a.G=(0,g.kk)(),a.o=new g.ce(a.ll,25,a),a.ll(b));
g.je(a.element,"ytp-upnext-autoplay-paused")},z9=function(a){y9(a);
a.G=(0,g.kk)();a.ll();g.M(a.element,"ytp-upnext-autoplay-paused")},y9=function(a){a.o&&(a.o.dispose(),a.o=null)},A9=function(a,b){g.JE.call(this,{J:"div",
ga:["html5-endscreen","ytp-player-content",b||"base-endscreen"]});this.O=a;this.L=!1},B9=function(a){a=g.T(a);
return a.Od&&!a.oa},C9=function(a,b){A9.call(this,a,"videowall-endscreen");
this.aa=a;this.V=b;this.D=0;this.g=[];this.F=this.B=this.A=null;this.G=this.M=!1;this.C=new g.Xn(this);g.K(this,this.C);this.H=new g.ce(g.z(g.M,this.element,"ytp-show-tiles"),0);g.K(this,this.H);b=new g.R({J:"button",ga:["ytp-button","ytp-endscreen-previous"],X:{"aria-label":g.P("YTP_PREVIOUS")},T:[{J:"svg",X:{height:"100%",version:"1.1",viewBox:"0 0 32 32",width:"100%"},T:[{J:"path",X:{d:"M 19.41,20.09 14.83,15.5 19.41,10.91 18,9.5 l -6,6 6,6 z",fill:"#fff"}}]}]});g.K(this,b);b.Ea(this.element);
b.R("click",this.GJ,this);this.K=new g.Pk({J:"div",Y:"ytp-endscreen-content"});g.K(this,this.K);this.K.Ea(this.element);b=new g.R({J:"button",ga:["ytp-button","ytp-endscreen-next"],X:{"aria-label":g.P("YTP_NEXT")},T:[{J:"svg",X:{height:"100%",version:"1.1",viewBox:"0 0 32 32",width:"100%"},T:[{J:"path",X:{d:"m 12.59,20.34 4.58,-4.59 -4.58,-4.59 1.41,-1.41 6,6 -6,6 z",fill:"#fff"}}]}]});g.K(this,b);b.Ea(this.element);b.R("click",this.FJ,this);this.o=new v9(a);g.K(this,this.o);g.Xs(this.O,this.o.element,
4);this.ua()},D9=function(a){return(0,g.S)(a.M,function(a){return g.KE(a)})},E9=function(a,b,c){return 0==b&&a.A.length&&(b=c/C9.b,2<=c/C9.b&&2<=b&&g.T(a.O).experiments.$("video_wall_emphasize_first"))?2*C9.b:C9.b},F9=function(a){var b=a.V.qo();
b!=a.M&&(a.M=b,a.O.W("autonavvisibility"))},G9=function(a){A9.call(this,a,"subscribecard-endscreen");
var b=a.getVideoData();this.g=new u9(a);g.K(this,this.g);g.Xs(this.O,this.g.element,4);this.o=new g.R(["div","ytp-subscribe-card",["img","ytp-author-image",{src:b.profilePicture}],["div","ytp-subscribe-card-right",["div","ytp-author-name",b.author],["div","html5-subscribe-button-container"]]]);g.K(this,this.o);this.o.Ea(this.element);this.A=new g.it(g.P("YTP_SUBSCRIBE"),g.P("YTP_UNSUBSCRIBE"),!0,b.kp,b.subscribed,"trailer-endscreen",a);g.K(this,this.A);this.A.Ea(this.o.wa["html5-subscribe-button-container"]);
this.ua()},H9=function(a){g.tn.call(this,a);
g.si({});this.b=null;this.isAvailable=!0;this.g=new g.Xn(this);g.K(this,this.g);this.o=g.T(a);B9(a)?this.b=new C9(this.O,this):this.o.oa?this.b=new G9(this.O):this.b=new A9(this.O);g.K(this,this.b);g.Xs(this.O,this.b.element,4);this.Mt();this.g.S(a,"videodatachange",this.Mt,this);this.g.S(a,"crn_endscreen",this.rJ,this);this.g.S(a,"crx_endscreen",this.sJ,this)};
g.A(s9,g.R);g.h=s9.prototype;g.h.jf=function(){var a=this.o.Ib().videoId;g.Z7(this.g.app,a,this.o.Qc,this.o.Wg(),void 0,void 0)};
g.h.IJ=function(a){g.dE(this.g,this);g.Em(a,this.g,!this.g.isFullscreen()&&this.B,this.o.Qc)&&this.jf()};
g.h.KJ=function(){this.Ba(this.A);this.A=null;t9(this)};
g.h.JJ=function(a){switch(a.keyCode){case 13:case 32:g.Hj(a)||(this.jf(),g.Gj(a))}};
g.h.LJ=function(a){120<g.Cj(a).naturalWidth&&g.M(this.element,"ytp-videowall-moving-thumbnail-loaded")};
g.A(u9,g.LE);u9.prototype.rb=function(a){a?this.A.show():g.ts(this.A)};
g.A(v9,g.R);g.h=v9.prototype;g.h.$i=function(){this.B&&(this.F.stop(),this.Ba(this.D),this.D=null,this.B.close(),this.B=null)};
g.h.ws=function(){this.rb(g.LD(this.g))};
g.h.GE=function(){window.focus();this.$i()};
g.h.ll=function(a){a=a||g.T(this.g).experiments.b("autoplay_time")||1E4;var b=Math.min((0,g.kk)()-this.G,a);a=Math.min(b/a,1);this.H.setAttribute("stroke-dashoffset",-293*(a+1));1<=a?this.select(!0):this.o&&this.o.start()};
g.h.select=function(a){var b=g.T(this.g);if(b.experiments.$("autonav_notifications")&&a&&window.Notification&&window.document.hasFocus){var c=window.Notification.permission;g.ks(this.g,"xwebnotifications",{permission:c});"default"==c?window.Notification.requestPermission():"granted"!=c||window.document.hasFocus()||(c=this.A.Ib(),this.$i(),this.B=new window.Notification(g.P("YTP_PLAYLIST_UP_NEXT"),{body:c.title,icon:c.Bc(b)}),this.D=this.S(this.B,"click",this.GE),this.F.start())}y9(this);this.g.mi(!1,
a)};
g.h.QE=function(a){!g.Qf(this.C.element,g.Cj(a))&&g.Em(a,this.g)&&this.select()};
g.h.ys=function(){g.VD(this.g,"autonavcancel");g.ND(this.g,!0)};
g.h.mL=function(a){120<g.Cj(a).naturalWidth&&g.M(this.element,"ytp-moving-thumbnail-loaded")};
g.h.gE=function(a){this.g.getPresentingPlayerType();this.show();x9(this,a)};
g.h.IH=function(a){this.g.getPresentingPlayerType();this.A&&this.A.Ib().videoId==a.Ib().videoId||w9(this,a)};
g.h.hE=function(){this.g.getPresentingPlayerType();y9(this);this.ua()};
g.h.U=function(){y9(this);this.$i();v9.N.U.call(this)};
g.A(A9,g.JE);A9.prototype.create=function(){this.L=!0};
A9.prototype.destroy=function(){this.L=!1};
A9.prototype.rl=function(){return!1};
g.A(C9,A9);C9.b=2;g.h=C9.prototype;g.h.create=function(){C9.N.create.call(this);var a=this.O.getVideoData();a&&(this.A=D9(a),this.B=a);this.uf();this.C.S(this.O,"appresize",this.uf);this.C.S(this.O,"videodatachange",this.HJ);this.C.S(this.O,"autonavchange",this.Dv);this.C.S(this.O,"autonavcancel",this.EJ);this.C.S(this.element,"transitionend",this.XF)};
g.h.destroy=function(){g.Zn(this.C);g.Mb(this.g);this.g=[];this.A=null;C9.N.destroy.call(this);g.je(this.element,"ytp-show-tiles");this.H.stop()};
g.h.rl=function(){return 1!=this.B.autonavState};
g.h.Vh=function(){return g.cE(this.O)&&this.rl()&&!this.F};
g.h.show=function(){C9.N.show.call(this);g.je(this.element,"ytp-show-tiles");g.T(this.O).isMobile?g.de(this.H):this.H.start();(this.G||this.F&&this.F!=this.B.clientPlaybackNonce)&&g.ND(this.O,!1);var a=this.Vh();g.cE(this.O)&&g.T(this.O).experiments.$("ui_logging")&&this.V.log({cancelButtonShow:a?"1":"0",state:this.rl()?"enabled":"disabled"});a?(F9(this),2==this.B.autonavState?g.T(this.O).experiments.$("fast_autonav_in_background")&&3==this.O.ov()?this.o.select(!0):x9(this.o):3==this.B.autonavState&&
z9(this.o)):(g.ND(this.O,!0),F9(this))};
g.h.ua=function(){C9.N.ua.call(this);z9(this.o);F9(this)};
g.h.XF=function(a){g.Cj(a)==this.element&&this.uf()};
g.h.uf=function(){if(this.A&&this.A.length){var a=g.T(this.O).experiments.$("video_wall_moving_thumbnails_hover");g.M(this.element,"ytp-endscreen-paginate");for(var b=g.On(this.element),c=b.width/b.height,d=96/54,e=C9.b,f=C9.b,k=Math.max(b.width/96,2),l=Math.max(b.height/54,2),m=this.A.length,p=Math.pow(C9.b,2),t=m*p,u=E9(this,0,l),x=E9(this,1,l),t=t+(Math.pow(u,2)-p),t=t+(Math.pow(x,2)-p),t=t-p;0<t&&(e<k||f<l);){var D=e/C9.b,E=f/C9.b,I=e<=k-C9.b&&t>=E*p,ga=f<=l-C9.b&&t>=D*p;if((D+1)/E*d/c>c/(D/(E+
1)*d)&&ga)t-=D*p,f+=C9.b;else if(I)t-=E*p,e+=C9.b;else if(ga)t-=D*p,f+=C9.b;else break}d=!1;k=C9.b+u;t>=3*p&&6>=m*p-t&&(f>=k||e>=k)&&x<=C9.b&&(d=!0);t=96*e;p=54*f;c=t/p<c?b.height/p:b.width/t;c=Math.min(c,2);t*=c;p*=c;t*=g.Ze(b.width/t||1,1,1.21);p*=g.Ze(b.height/p||1,1,1.21);t=Math.floor(Math.min(b.width,t));p=Math.floor(Math.min(b.height,p));b=this.K.element;g.Nn(b,t,p);g.xn(b,{marginLeft:t/-2+"px",marginTop:p/-2+"px"});w9(this.o,this.A[0]);g.le(this.element,"ytp-endscreen-takeover",this.Vh());
F9(this);c=t+4;t=p+4;p=0;k=!this.Vh();l=!1;for(D=0;D<e;D++)for(E=0;E<f;E++)if(I=x>C9.b&&1<=p&&!l?p+1:p,ga=0,d&&D>=e-C9.b&&E>=f-C9.b?ga=1:0==E%C9.b&&0==D%C9.b&&(E<u&&D<u?0==E&&0==D&&(ga=u):x>C9.b&&E>=f-x&&D>=e-x?E==f-x&&D==e-x&&(l=!0,I=1,ga=x):ga=C9.b),I=(I+this.D)%m,I=0>I*m?I+m:I,0!=ga){var ka=this.g[p];ka||(ka=new s9(this.O),this.g[p]=ka,b.appendChild(ka.element));var Va=Math.floor(t*E/f),nb=Math.floor(c*D/e),Bb=Math.floor(t*(E+ga)/f)-Va-4,nd=Math.floor(c*(D+ga)/e)-nb-4;g.Dn(ka.element,nb,Va);g.Nn(ka.element,
nd,Bb);g.xn(ka.element,"transitionDelay",(E+D)/20+"s");g.le(ka.element,"ytp-videowall-still-mini",1==ga);g.le(ka.element,"ytp-videowall-still-large",2<ga);ga=ka;I=this.A[I];ka=k&&!a;ga.o=I;Va=g.T(ga.g);r9(ga,I,Va,g.ge(ga.element,"ytp-videowall-still-large")?"hqdefault.jpg":"mqdefault.jpg");g.je(ga.element,"ytp-videowall-moving-thumbnail-loaded");ga.update({moving_thumbnail:"data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7"});ka?(g.M(ga.element,"ytp-videowall-active"),
t9(ga)):Va.experiments.$("video_wall_moving_thumbnails_hover")&&!ga.A&&(ga.A=ga.R("mouseover",ga.KJ));Va=I.Qc;ka=ga.g;I=ga;Va=Va&&Va.itct;g.T(ka).experiments.$("player_interaction_logging")&&(ga=ka.app.ca,ka=Va,I=I.element.getAttribute("data-visual-id"),g.eE(ga,"onLogServerVeCreated",{id:I,tracking_params:ka}));p++}g.le(this.element,"ytp-endscreen-paginate",p<m);for(a=this.g.length-1;a>=p;a--)ka=this.g[a],g.If(ka.element),g.Lb(ka);this.g.length=p}};
C9.o=2;C9.g=1.21;g.h=C9.prototype;g.h.HJ=function(){var a=this.O.getVideoData();this.B!=a&&(this.D=0,this.A=D9(a),this.B=a,this.uf())};
g.h.FJ=function(){this.D+=this.g.length;this.uf()};
g.h.GJ=function(){this.D-=this.g.length;this.uf()};
g.h.WB=function(){return!!this.o.o};
g.h.Dv=function(a){1==a?(this.G=!1,this.F=this.B.clientPlaybackNonce,y9(this.o),this.b&&this.uf()):(this.G=!0,this.b&&this.Vh()&&(2==a?x9(this.o):3==a&&z9(this.o)))};
g.h.EJ=function(a){if(a){for(a=0;a<this.g.length;a++)g.fE(this.aa,this.g[a],!0);this.Dv(1)}else this.F=null,this.G=!1;this.uf()};
g.A(G9,A9);G9.prototype.show=function(){G9.N.show.call(this);this.g.rb(!0)};
G9.prototype.ua=function(){G9.N.ua.call(this);this.g.rb(!1)};
g.A(H9,g.tn);g.h=H9.prototype;g.h.Bv=function(){var a=this.O.getVideoData(),b=!B9(this.O)||!(!a.M||!a.M.length),a=g.rn(a,"ypc_module"),c=g.I4(this.O.app);return(b||!1)&&!a&&!c};
g.h.qo=function(){return(this.b instanceof C9||!1)&&this.b.b&&this.b.Vh()};
g.h.UB=function(){return this.qo()?this.b.WB():!1};
g.h.U=function(){g.ej(this.O,"endscreen");H9.N.U.call(this)};
g.h.load=function(){H9.N.load.call(this);this.b.show();g.T(this.O).oa&&.01>Math.random()&&this.log({trailerEndscreenShow:1})};
g.h.log=function(a){g.ks(this.O,"end",a)};
g.h.unload=function(){H9.N.unload.call(this);this.b.ua();this.b.destroy();this.isAvailable=!1};
g.h.rJ=function(a){this.Bv()&&(this.b.L||this.b.create(),"load"==a.getId()&&this.load())};
g.h.sJ=function(a){"load"==a.getId()&&this.loaded&&this.unload()};
g.h.Mt=function(){g.ej(this.O,"endscreen");var a=Math.max(1E3*(this.O.getVideoData().lengthSeconds-10),0),a=new g.$i(a,0x8000000000000,{id:"preload",namespace:"endscreen"}),b=new g.$i(0x8000000000000,0x8000000000000,{id:"load",priority:6,namespace:"endscreen"});this.O.wb([a,b])};
window._exportCheck==g.sa&&g.aa("ytmod.player.endscreen",H9,void 0);})(_yt_player);
