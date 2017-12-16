$fn = 64;

batterylength = 43;
batterywidth = 34;
batteryheight = 5;

pcblength = 43;
pcbwidth = 34;
pcbheight = 5;

petrudestart = 5;
petrudeinlet = 10;
petrudelength = 10;
startangle = 63.5;
startsupport = 11;
petrudeangle = 113.6;
petrudesupport = 24.9;

roundness = 2;
tolerance = 1;
pcbtolerance = 0.1;
overpcb = 4;
overpcb2 = 2;

ledhole = 1.25;
buttonhole = 6;

pcbthickness = 1.6;
esptickness = 5;

coillength = 42;
coilwidth = 30;
coilheight = 1; //eigentlich 0.5

usbstart = coilheight+batteryheight+pcbthickness;
usbheight = 3;
usbwidth = 8;

standoffradius = 4;
standoffheight = coilheight+batteryheight;
standofflengthloss = 6.4;

screwradius = 1.25;
screwheight = 4;
screwhead = 2.5;

nutradius = 2.75;
nutheight = 2;

thickness = 1;
length = batterylength+tolerance+2*standofflengthloss+5*thickness;
width = batterywidth+tolerance+2*thickness;
height = 14;

innerlength = length-5*thickness;
innerwidth = width-2*thickness;
innerheight = height-2*thickness;

lowerheight = usbstart+usbheight+roundness;
upperheight = height-lowerheight;

hole1frommid = width/2-(17-2.3);
hole2frommid = width/2-(17-31.7);
holefromedge = 2.3+pcbtolerance;

loadingfrommid = width/2-(17-25);
loadingfromedge = 3+pcbtolerance;

emptyfrommid = width/2-(17-2);
emptyfromedge = 21+pcbtolerance;

alarmfrommid = width/2-(17-14);
alarmfromedge = 41+pcbtolerance;

activefrommid = width/2-(17-19);
activefromedge = 37+pcbtolerance;

buttonfrommid = width/2-(17-11);
buttonfromedge = 40+pcbtolerance;

key1frommid = width/2-7;
key2frommid = width/2+7;

module corner (x, y, z) {
    translate([x, y, z]) sphere(roundness);
}

module edge (x, y, z, ax, ay, az, l) {
    translate([x, y, z]) rotate([ax, ay, az]) cylinder(r = roundness, h = l);
} 

module area (x, y, z, l, w, h) {
    translate([x, y, z]) cube([l, w, h]);
}

module rotarea (x, y, z, ax, ay, az, l, w, h) {
    translate([x, y, z]) rotate([ax, ay, az]) cube([l, w, h]);
}
module lowerouterbody (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){  
        //bottom
        area(roundness, roundness, 0, length-3*roundness, width-2*roundness, thickness);
        
        //outer lower corners
        corner(roundness, roundness, roundness);
        corner(roundness, width-roundness, roundness);
        corner(length-2*roundness, roundness, roundness);
        corner(length-2*roundness, width-roundness, roundness);
        
        //outer lower edges
        edge(roundness, roundness, roundness, -90, 0, 0, width-2*roundness);
        edge(roundness, roundness, roundness, 0, 90, 0, length-3*roundness);
        edge(length-2*roundness, roundness, roundness, -90, 0, 0, width-2*roundness);
        edge(roundness, width-roundness, roundness, 0, 90, 0, length-3*roundness);
        
        //outer upper corners
        edge(roundness, roundness, roundness, 0, 0, 0, usbstart+usbheight-(roundness-thickness));
        edge(roundness, width-roundness, roundness, 0, 0, 0, usbstart+usbheight-(roundness-thickness));
        edge(length-2*roundness, roundness, roundness, 0, 0, 0, usbstart+usbheight-(roundness-thickness));
        edge(length-2*roundness, width-roundness, roundness, 0, 0, 0, usbstart+usbheight-(roundness-thickness));
        
        //outer upper edges
        area(0, roundness, roundness, thickness, width-2*roundness, usbstart+usbheight-(roundness-thickness));
        area(roundness, 0, roundness, length-3*roundness, thickness, usbstart+usbheight-(roundness-thickness));
        area(roundness, width-thickness, roundness, length-3*roundness, thickness, usbstart+usbheight-(roundness-thickness)); 
        
        //back wall
        area(length-2*roundness, roundness, roundness, 2*thickness, width-2*roundness, lowerheight-roundness-thickness);
    }
}

module lowerinnerbody (x, y, z, ax, ay, az) {
    translate([x+thickness, y+thickness, z+thickness]) rotate ([ax, ay, az]) union(){
        area(0, 0, 0, innerlength, innerwidth, innerheight);
    }
}

module lowerkeychainwalls (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
       area(length-3*thickness-holefromedge-standoffradius, key1frommid, thickness, 2*thickness, width-2*(hole1frommid+2*standoffradius), lowerheight-roundness);
        area(length-3*thickness-holefromedge-standoffradius, key1frommid, thickness, holefromedge+standoffradius, 2*thickness, lowerheight-roundness);
        area(length-3*thickness-holefromedge-standoffradius, key2frommid-2*thickness, thickness, holefromedge+standoffradius, 2*thickness, lowerheight-roundness);
    }
}
module keychaincutout (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        area(length-thickness-holefromedge-standoffradius, key1frommid+2*thickness, -2*thickness, holefromedge+thickness, 10, 2*height);
    }
}
module petrude (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) difference(){
        union(){
            //lower corner
            corner(length+petrudestart-roundness, roundness, roundness);
            corner(length+petrudelength-roundness, petrudeinlet+roundness, roundness);
            
            //lower edges
            edge(length-roundness, roundness, roundness, 0, 90, 0, petrudestart);
            edge(length+petrudestart-roundness, roundness, roundness, -startangle, 90, 0, startsupport);
            edge(length+petrudelength-roundness, petrudeinlet+roundness, roundness, -petrudeangle, 90, 0, petrudesupport);
            
            //mid edge
            edge(length+petrudestart-roundness, roundness, roundness, 0, 0, 0, height-2*roundness);
            edge(length+petrudelength-roundness, petrudeinlet+roundness, roundness, 0, 0, 0, height-2*roundness);
            edge(length-roundness, roundness, roundness, 0, 0, 0, height-2*roundness);
            edge(length-roundness, width-roundness, roundness, 0, 0, 0, height-2*roundness);
            //support
            rotarea(length+petrudestart-0.25, roundness-1, roundness, 0, 0, startangle, startsupport, 2*roundness, height-2*roundness);
            rotarea(length+petrudelength-0.05, petrudeinlet+roundness+0.5, roundness, 0, 0, petrudeangle, petrudesupport+0.3, 2*roundness, height-2*roundness);
            
            //backside transition
            intersection(){
                //rotarea(length+petrudelength-roundness, roundness+0.5, roundness, 0, 0, petrudeangle, petrudesupport, roundness, height-roundness);
                //area(length-2*roundness, roundness, roundness, 2*roundness, width-2*roundness, height-roundness);
            }
            
            //petrude
            area(length-roundness, 0, roundness, petrudestart, 2*roundness, height-2*roundness);
            //backside
            area(length-2*roundness, roundness, roundness, 2*roundness, width-5*roundness, height-2*roundness);
             edge(length-roundness, roundness, height-roundness, -90, 0, 0, width-2*roundness);
            //outer fill
            area(length-2*roundness, width-roundness, roundness, roundness, roundness, height-2*roundness);
            area(length-2*roundness, 0, roundness, roundness, roundness, height-2*roundness);
            //inner fill
            //area(length-2*roundness, roundness, roundness, 2*roundness, roundness, height-roundness);
            area(length-2*roundness, width-4*roundness, roundness, roundness, 3*roundness, height-roundness);
            
            //upper corner
            corner(length+petrudestart-roundness, roundness, height-roundness);
            corner(length+petrudelength-roundness, petrudeinlet+roundness, height-roundness);
            corner(length-roundness, roundness, height-roundness);
            corner(length-roundness, width-roundness, height-roundness);
            edge(length-roundness, roundness, height-roundness, -90, 0, 90, roundness);
            edge(length-roundness, width-roundness, height-roundness, -90, 0, 90, roundness);
            
            //upper edge
            edge(length-roundness, roundness, height-roundness, 0, 90, 0, petrudestart);
            edge(length+petrudestart-roundness, roundness, height-roundness, -startangle, 90, 0, startsupport);
            edge(length+petrudelength-roundness, petrudeinlet+roundness, height-roundness, -petrudeangle, 90, 0, petrudesupport);
        }
        union(){
            //area(length-2*roundness, 4*roundness, height-thickness, 2*roundness, width-8*roundness, thickness);
        }
    }
}

module usbcutout (x, y, z, ax, ay, az) {
    translate([x, width/2-usbwidth/2, z+thickness+usbstart]) rotate ([ax, ay, az]) union(){
            cube([thickness, usbwidth, usbheight]);
    }
}

module battery (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
            cube([batterylength, batterywidth, batteryheight]);
    }
}
            
module pcb (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        cube([pcblength, pcbwidth, pcbthickness]);
    }
}

module upperouterbody (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        //bottom
        area(roundness, roundness, -thickness, length-3*roundness, width-2*roundness, thickness);
        
        //outer lower corners
        corner(roundness, roundness, -roundness);
        corner(roundness, width-roundness, -roundness);
        corner(length-2*roundness, roundness, -roundness);
        corner(length-2*roundness, width-roundness, -roundness);
        
        //outer lower edges
        edge(roundness, roundness, -roundness, -90, 0, 0, width-2*roundness);
        edge(roundness, roundness, -roundness, 0, 90, 0, length-3*roundness);
        edge(length-2*roundness, roundness, -roundness, -90, 0, 0, width-2*roundness);
        edge(roundness, width-roundness, -roundness, 0, 90, 0, length-3*roundness);
        
        //outer upper corners
        edge(roundness, roundness, -2*roundness, 0, 0, 0, roundness);
        edge(roundness, width-roundness, -2*roundness, 0, 0, 0, roundness);
        //edge(length-roundness, roundness, -2*roundness, 0, 0, 0, roundness);
        //edge(length-roundness, width-roundness, -2*roundness, 0, 0, 0, roundness);
        
        //outer upper edges
        area(0, roundness, -2*roundness, thickness, width-2*roundness, roundness);
        area(roundness, 0, -2*roundness, length-3*roundness, thickness, roundness);
        area(roundness, width-thickness, -2*roundness, length-3*roundness, thickness, roundness); 
        //area(length-4*thickness, roundness, -roundness-thickness, 2*thickness, width-2*roundness, roundness); 
        
    }
}
module upperkeychainwalls (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        area(length-3*thickness-holefromedge-standoffradius, key1frommid, -thickness-upperheight, 2*thickness, width-2*(hole1frommid+2*standoffradius), upperheight);
        area(length-3*thickness-holefromedge-standoffradius, key1frommid, -thickness-upperheight, holefromedge+standoffradius, 2*thickness, upperheight);
        area(length-3*thickness-holefromedge-standoffradius, key2frommid-2*thickness, -thickness-upperheight, holefromedge+standoffradius, 2*thickness, upperheight);
    }
}

module upperinnerbody (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        area(thickness, thickness, -2*upperheight-thickness, length-5*thickness, innerwidth, 2*upperheight);
        area(0, 0, -3*upperheight-thickness, length, width, 2*upperheight);
        area(length-2*thickness, 0, -2*roundness, roundness, width, 2*roundness);
    }
}

module lowerbody (x, y, z, ax, ay, az) {
    union(){
        difference(){
            lowerouterbody (x, y, z, ax, ay, az);
            lowerinnerbody (x, y, z, ax, ay, az);
            usbcutout (x, y, z, ax, ay, az);
        }
    }
}

module upperbody (x, y, z, ax, ay, az) {
    union(){
        //upperinnerbody (x, y, z, ax, ay, az);
        difference(){
            upperouterbody (x, y, z, ax, ay, az);
            upperinnerbody (x, y, z, ax, ay, az);
            usbcutout (x, y, z, ax, ay, az);
        }
    }
}

module standoffs (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        translate([thickness+holefromedge,hole1frommid,thickness]) difference(){
            intersection(){
                cylinder(r = standoffradius, h = standoffheight);
                translate([-(thickness+holefromedge),-hole1frommid,0])lowerinnerbody (x, y, z, ax, ay, az);
            }
            cylinder(r = screwradius, h = standoffheight);
            translate ([0,0,standoffheight-nutheight]) rotate([0,0,90]) cylinder(r = nutradius, h = nutheight, $fn = 6);
        }
        
        translate([thickness+holefromedge,hole2frommid,thickness]) difference() {
            intersection(){
                cylinder(r = standoffradius, h = standoffheight);
                translate([-(thickness+holefromedge),-hole2frommid,0])lowerinnerbody (x, y, z, ax, ay, az);
            }
            cylinder(r = screwradius, h = standoffheight);
            translate ([0,0,standoffheight-nutheight]) rotate([0,0,90]) cylinder(r = nutradius, h = nutheight, $fn = 6);
        }
        
        translate([length-4*thickness-holefromedge,hole1frommid,thickness]) difference() {
            intersection(){
                cylinder(r = standoffradius, h = standoffheight);
                translate([-(length-4*thickness-holefromedge),-hole1frommid,0])lowerinnerbody (x, y, z, ax, ay, az);
            }
            cylinder(r = screwradius, h = standoffheight);
            translate ([0,0,standoffheight-nutheight]) rotate([0,0,90]) cylinder(r = nutradius, h = nutheight, $fn = 6);
        }
        
        translate([length-4*thickness-holefromedge,hole2frommid,thickness]) difference() {
            intersection(){
                cylinder(r = standoffradius, h = standoffheight);
                translate([-(length-4*thickness-holefromedge),-hole2frommid,0])lowerinnerbody (x, y, z, ax, ay, az);
            }
            cylinder(r = screwradius, h = standoffheight);
            translate ([0,0,standoffheight-nutheight]) rotate([0,0,90]) cylinder(r = nutradius, h = nutheight, $fn = 6);
        }
    }
}  

module cutouts (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        translate([loadingfromedge,loadingfrommid,-thickness-overpcb2]) cylinder(r = ledhole, h = thickness+overpcb2);
        translate([emptyfromedge,emptyfrommid,-thickness-overpcb2]) cylinder(r = ledhole, h = thickness+overpcb2);
        translate([alarmfromedge,alarmfrommid,-thickness-overpcb2]) cylinder(r = ledhole, h = thickness+overpcb2);
        translate([activefromedge,activefrommid,-thickness-overpcb2]) cylinder(r = ledhole, h = thickness+overpcb2);
        translate([buttonfromedge,buttonfrommid,-thickness-overpcb2]) cylinder(r = buttonhole, h = thickness+overpcb2);
        translate([thickness+holefromedge,hole1frommid,-thickness]) cylinder(r = standoffradius-thickness, h = thickness);
        translate([length-4*thickness-holefromedge,hole2frommid,-thickness]) cylinder(r = standoffradius-thickness, h = thickness);
    }
}

module ledouts (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        intersection(){
            translate([loadingfromedge,loadingfrommid,-thickness-overpcb2]) cylinder(r = ledhole+thickness, h = overpcb2);
            translate([0,0,-4*thickness])lowerinnerbody (0, 0, 0, 0, 0, 0);
        }
        translate([emptyfromedge,emptyfrommid,-thickness-overpcb2]) cylinder(r = ledhole+thickness, h = overpcb2);
        translate([alarmfromedge,alarmfrommid,-thickness-overpcb2]) cylinder(r = ledhole+thickness, h = overpcb2);
        translate([activefromedge,activefrommid,-thickness-overpcb2]) cylinder(r = ledhole+thickness, h = overpcb2);
        translate([buttonfromedge,buttonfrommid,-thickness-overpcb2]) cylinder(r = buttonhole+thickness, h = overpcb2);
    }
}

module screwholes (x, y, z, ax, ay, az) {
    translate([x, y, z]) rotate ([ax, ay, az]) union(){
        translate([thickness+holefromedge,hole1frommid,-thickness-overpcb]) difference(){         
            intersection(){
                cylinder(r = standoffradius, h = overpcb);
                translate([-(thickness+holefromedge),-hole1frommid,-2*thickness])lowerinnerbody (0, 0, 0, 0, 0, 0);
            }
            cylinder(r1 = screwradius, r2 = standoffradius-thickness, h = overpcb);
        }
        
    translate([length-4*thickness-holefromedge,hole2frommid,-thickness-overpcb]) difference(){         
            intersection(){
                cylinder(r = standoffradius, h = overpcb);
                translate([-(length-4*thickness-holefromedge),-hole2frommid,-2*thickness])lowerinnerbody (, 0, 0, 0, 0, 0);
            }
            cylinder(r1 = screwradius, r2 = standoffradius-thickness, h = overpcb);
        }
    }
}

module lowerbodyfull (x, y, z, ax, ay, az) {
    lowerbody(x, y, z, ax, ay, az);    
    standoffs(x, y, z, ax, ay, az);
}

module upperbodyfull (x, y, z, ax, ay, az) {
    difference(){
        union(){
            upperbody(x, y, z, ax, ay, az);
            ledouts(x, y, z, ax, ay, az);
            screwholes(x, y, z, ax, ay, az);
        }
    cutouts(x, y, z, ax, ay, az);
    }
}
        


difference(){
    union(){
        lowerbodyfull(0, 0, 0, 0, 0, 0);
        lowerkeychainwalls(0, 0, 0, 0, 0, 0);
        //battery(7.6, 1.5, 3, 0, 0, 0);
        //pcb(1, 1.5, standoffheight+thickness, 0, 0, 0);
    }
    keychaincutout(0, 0, 0, 0, 0, 0);
}
    
difference(){
    union(){
        //upperbodyfull(0, 0, height, 0, 0, 0);
        //upperkeychainwalls(0, 0, height, 0, 0, 0);
        upperbodyfull(length, 50, 0, 0, 180, 0);
        upperkeychainwalls(length, 50, 0, 0, 180, 0);
    }
    //keychaincutout(0, 0, height, 0, 0, 0);
    keychaincutout(length, 50, 0, 0, 180, 0);
}
