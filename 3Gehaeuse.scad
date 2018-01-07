$fn = 64;

batterylength = 43;
batterywidth = 34;
batteryheight = 5;

pcblength = 43;
pcbwidth = 34;
pcbheight = 5;
pcbthickness = 1.6;

pcbtolerance = 0.1;
overpcb = 4;
overpcb2 = 2;

ledhole = 1.25;
buttonhole = 9;

coillength = 42;
coilwidth = 30;
coilheight = 0.5; //eigentlich 0.5

screwradius = 1.25;
screwheight = 4;
screwhead = 2.5;

nutradius = 3.3;
nutheight = 2;

roundness = 2;
tolerance = 1.5;
thickness = 1.5;

width = batterywidth+tolerance+2*thickness;

hole1frommid = width/2-(17-2.3);
hole2frommid = width/2-(17-31.7);
holefromedge = thickness+2.3+0.3+pcbtolerance;
hole2fromhole1 = 54.4;

mount1frommid = width/2-(17-6.7);
mount2frommid = width/2-(17-27.3);

standoffradius = 4;
standoffheight = coilheight+batteryheight;
standofflengthloss = holefromedge+standoffradius;


length = 2*holefromedge+hole2fromhole1;
height = coilheight+batteryheight+pcbheight+tolerance+2*thickness;

upperstandoffheight = height-standoffheight-2*thickness-3;

usbstart = thickness+coilheight+batteryheight+pcbthickness;
usbheight = 3;
usbwidth = 8;

lowerheight = usbstart+usbheight;
upperheight = height-lowerheight;

loadingfrommid = width/2-(17-32);
loadingfromedge = 47+holefromedge-2.3;

emptyfrommid = width/2-(17-2);
emptyfromedge = 47+holefromedge-2.3;

activefrommid = width/2-(17-11);
activefromedge = 43+holefromedge-2.3;

buttonfrommid = width/2-(17-17);
buttonfromedge = 20+holefromedge-2.3;

key1frommid = width/2-7;
key2frommid = width/2+7;


echo(upperstandoffheight);
echo(standoffheight);
echo(height);

module battery (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
            cube([batterylength, batterywidth, batteryheight]);
    }
}
module corner (x, y, z, r) {
    translate([x, y, z]) sphere(r);
}

module edge (x, y, z, ax, ay, az, l, r, fn = $fn) {
    translate([x, y, z]) rotate([ax, ay, az]) cylinder(r = r, h = l, $fn=fn);
} 

module area (x, y, z, l, w, h) {
    translate([x, y, z]) cube([l, w, h]);
}

module rotarea (x, y, z, ax, ay, az, l, w, h) {
    translate([x, y, z]) rotate([ax, ay, az]) cube([l, w, h]);
}

module roundedcube (x, y, z, ax, ay, az, l, w, h, r){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        //infill
        area (r, r, 0, l-2*r, w-2*r, h);
        area (0, r, r, l, w-2*r, h-2*r);
        area (r, 0, r, l-2*r, w, h-2*r);
        
        //lower corners
        corner (r, r, r, r);
        corner (r, w-r, r, r);
        corner (l-r, r, r, r);
        corner (l-r, w-r, r, r);
        
        //lower edges
        edge (r, r, r, -90, 0, 0, w-2*r, r);
        edge (r, r, r, 0, 90, 0, l-2*r, r);
        edge (l-r, r, r, -90, 0, 0, w-2*r, r);
        edge (r, w-r, r, 0, 90, 0, l-2*r, r);
        
        //mid corner
        edge (r, r, r, 0, 0, 0, h-2*r, r);
        edge (r, w-r, r, 0, 0, 0, h-2*r, r);
        edge (l-r, r, r, 0, 0, 0, h-2*r, r);
        edge (l-r, w-r, r, 0, 0, 0, h-2*r, r);
        
        //upper corners
        corner (r, r, h-r, r);
        corner (r, w-r, h-r, r);
        corner (l-r, r, h-r, r);
        corner (l-r, w-r, h-r, r);
        
        //upper edges
        edge (r, r, h-r, -90, 0, 0, w-2*r, r);
        edge (r, r, h-r, 0, 90, 0, l-2*r, r);
        edge (l-r, r, h-r, -90, 0, 0, w-2*r, r);
        edge (r, w-r, h-r, 0, 90, 0, l-2*r, r);
    }
}

module cubecutout (x, y, z, ax, ay, az, l, w, h, r, t){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        area (t, t, t, l-2*t, w-2*t, h-2*t);
    }
}

module cutroundcube (x, y, z, ax, ay, az, l, w, h, r, t, ch){
    difference(){
        roundedcube (x, y, z, ax, ay, az, l, w, h, r);
        cubecutout (x, y, z, ax, ay, az, l, w, h, r, t);
        rotarea (x, y, z+ch, ax, ay, az, l+2, w+2, h);
    }
}
    
module standoff (x, y, z, or, ir, nr, sh, nh){  
    difference(){
        edge (x, y, z, 0, 0, 0, sh, or);
        edge (x, y, z, 0, 0, 0, sh, ir);
        edge (x, y, z+sh-nh, 0, 0, 90, nh, nr, 6);
    }
}  

module lowerstandoffs (x, y, z, ax, ay, az, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        standoff (hfe, hfm1, t, or, ir, nr, sh, nh);
        standoff (hfe, hfm2, t, or, ir, nr, sh, nh);
        standoff (hfe+hf2, hfm1, t, or, ir, nr, sh, nh);
        standoff (hfe+hf2, hfm2, t, or, ir, nr, sh, nh);
    }
}
module nutcutout (x, y, z, ax, ay, az, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        edge (hfe, hfm1, t+sh-nh, 0, 0, 90, h, nr, 6);
        edge (hfe, hfm2, t+sh-nh, 0, 0, 90, h, nr, 6);
        edge (hfe+hf2, hfm2, t+sh-nh, 0, 0, 90, h, nr, 6);
        edge (hfe+hf2, hfm1, t+sh-nh, 0, 0, 90, h, nr, 6);
    }
}
module keychainwalls (x, y, z, ax, ay, az, l, w, h, r, t, ch, kfm1, kfm2){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        area (l-4*t, kfm1, t, 3*t, t, ch-t);
        area (l-4*t, kfm2-t, t, 3*t, t, ch-t);
        area (l-4*t, kfm1, t, t, kfm2-kfm1, ch-t);
    }
}

module keychaincutout (x, y, z, ax, ay, az, l, w, h, r, t, ch, kfm1, kfm2){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        area (l-3*t, kfm1+t, 0, 2*t, kfm2-kfm1-2*t, h);
    }
}

module usbcutout (x, y, z, ax, ay, az, w, t, usbw, usbh, usbs){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        area (0, w/2-usbw/2, usbs, t, usbw, usbh);
    }
}

module buttonhole (x, y, z, ax, ay, az, t, but, bfm, bfe){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        edge (bfe+t, bfm, -1, 0, 0, 0, t+1, but);
    }
}

module ledholes (x, y, z, ax, ay, az, t, led, lfm, lfe, efm, efe, cfm, cfe){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        edge (lfe+t, lfm, 0, 0, 0, 0, t, led);
        edge (efe+t, efm, 0, 0, 0, 0, t, led);
        //edge (afe+t, afm, 0, 0, 0, 0, t, led);
        edge (cfe+t, cfm, 0, 0, 0, 0, t, led);
    }
}

module mount (x, y, z, or, ir, sh, nh){  
        edge (x, y, z, 0, 0, 0, sh, or);
        edge (x, y, z, 0, 0, 0, sh+nh, ir);
}  

module lowermounts (x, y, z, ax, ay, az, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, mfm1, mfm2, hfm1, hfm2){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        difference(){
            mount (hfe, mfm1, t, or, ir, sh, nh);
            edge (hfe, hfm1, t, 0, 0, 0, sh, ir);
        }
        difference(){
            mount (hfe, mfm2, t, or, ir, sh, nh);
            edge (hfe, hfm2, t, 0, 0, 0, sh, ir);
        }
        difference(){
            mount (hfe+hf2, mfm1, t, or, ir, sh, nh);
            edge (hfe+hf2, hfm1, t, 0, 0, 0, sh, ir);
        }
        difference(){
            mount (hfe+hf2, mfm2, t, or, ir, sh, nh);
            edge (hfe+hf2, hfm2, t, 0, 0, 0, sh, ir);
        }
    }
}

module lowerpart (x, y, z, ax, ay, az, l, w, h, r, t, ch, usbw, usbh, usbs, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2, kfm1, kfm2, mfm1, mfm2){ 
    difference(){
        union(){
            cutroundcube (x, y, z, ax, ay, az, l, w, h, r, t, ch);
            lowerstandoffs (x, y, z, ax, ay, az, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2);
            keychainwalls (x, y, z, ax, ay, az, l, w, h, r, t, ch, kfm1, kfm2);
            lowermounts (x, y, z, ax, ay, az, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, mfm1, mfm2, hfm1, hfm2);
        }
        keychaincutout (x, y, z, ax, ay, az, l, w, h, r, t, ch, kfm1, kfm2);
        usbcutout (x, y, z, ax, ay, az, w, t, usbw, usbh, usbs);
        nutcutout (x, y, z, ax, ay, az, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2);
    }
}   
module ustandoff (x, y, z, or, sh){  
    edge (x, y, z, 0, 0, 0, sh, or);
}
module upperstandoffs (x, y, z, ax, ay, az, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        intersection(){
            cubecutout (0, 0, 0, 0, 0, 0, l, w, h, r, t);
            ustandoff (hfe, hfm1, t, or, sh);
        }
        intersection(){
            cubecutout (0, 0, 0, 0, 0, 0, l, w, h, r, t);
            ustandoff (hfe, hfm2, t, or, sh);
        }
        intersection(){
            cubecutout (0, 0, 0, 0, 0, 0, l, w, h, r, t);
            ustandoff (hfe+hf2, hfm1, t, or, sh);
        }
        intersection(){
            cubecutout (0, 0, 0, 0, 0, 0, l, w, h, r, t);
            ustandoff (hfe+hf2, hfm2, t, or, sh);
        }
    }
}

module screwhole (x, y, z, t, ir, nr, sh){  
    edge (x, y, z-t, 0, 0, 0, sh-t+5, nr);
    edge (x, y, z-3, 0, 0, 0, sh+t, ir);
}

module upperscrewholes (x, y, z, ax, ay, az, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2){
    translate([x, y, z]) rotate([ax, ay, az]) union(){
        screwhole (hfe, hfm1, t, t, ir, nr, sh);
        screwhole (hfe, hfm2, t, t, ir, nr, sh);
        screwhole (hfe+hf2, hfm1, t, t, ir+0.1, nr, sh);
        screwhole (hfe+hf2, hfm2, t, t, ir+0.1, nr, sh);
    }
}


module upperpart (x, y, z, ax, ay, az, l, w, h, r, t, ch, usbw, usbh, usbs, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2, kfm1, kfm2, led, but, lfm, lfe, efm, efe, afm, afe, cfm, cfe, bfm, bfe){ 
    translate([x, y, z]) rotate([ax, ay, az]) difference(){
        union(){
            cutroundcube (0, 0, 0, 0, 0, 0, l, w, h, r, t, -ch);
            upperstandoffs (0, 0, h-sh-2*t, 0, 0, 0, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2);
            keychainwalls (0, 0, h-ch-t, 0, 0, 0, l, w, h, r, t, ch, kfm1, kfm2);
        }
        keychaincutout (0, 0, t, 0, 0, 0, l, w, h, r, t, ch, kfm1, kfm2);
        buttonhole (0, 0, h-t, 0, 0, 0, t, but, bfm, bfe);
        ledholes (0, 0, h-t, 0, 0, 0, t, led, lfm, lfe, efm, efe, cfm, cfe);
        upperscrewholes (0, 0, h-ch-0.2, 0, 0, 0, l, w, h, r, t, or, ir, nr, sh, nh, hfe, hf2, hfm1, hfm2);
    }
}  

lowerpart (x=0, y=0, z=0, ax=0, ay=0, az=0, l=length, w=width, h=height, r=roundness, t=thickness, ch=lowerheight, usbw=usbwidth, usbh=usbheight, usbs=usbstart, or=standoffradius, ir=screwradius, nr=nutradius, sh=standoffheight, nh=nutheight, hfe=holefromedge, hf2=hole2fromhole1, hfm1=hole1frommid, hfm2=hole2frommid, kfm1=key1frommid, kfm2=key2frommid, mfm1=mount1frommid, mfm2=mount2frommid);

upperpart (x=length, y=50, z=height, ax=0, ay=180, az=0, l=length, w=width, h=height, r=roundness, t=thickness, ch=upperheight, usbw=usbwidth, usbh=usbheight, usbs=usbstart, or=standoffradius, ir=screwradius, nr=screwhead, sh=upperstandoffheight, nh=nutheight, hfe=holefromedge, hf2=hole2fromhole1, hfm1=hole1frommid, hfm2=hole2frommid, kfm1=key1frommid, kfm2=key2frommid, led=ledhole, but=buttonhole, lfm=loadingfrommid, lfe=loadingfromedge, efm=emptyfrommid, efe=emptyfromedge, cfm=activefrommid, cfe=activefromedge, bfm=buttonfrommid, bfe=buttonfromedge);


//battery (9, 3, 2, 0, 0, 0);   