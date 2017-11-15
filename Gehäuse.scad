$fn = 64; 

length = 65;
width = 43;
height = 20;
thickness = 2;

edges = 5;
inneredges = edges+thickness;

holes = 9;
outerdia = 4;
innerdia = 2;

batterythickness = 8;
innerheight = batterythickness+4;

pcbthickness = 2;

usblength = 4;
usbwidth = 12;
usbheight = 7;

clearance = 0.1;

//lower body
union(){
    difference(){
        union(){
            //outer lower cornes
            translate([edges,edges,edges]) sphere(edges);
            translate([length-edges,edges,edges]) sphere(edges);
            translate([edges,width-edges,edges]) sphere(edges);    
            translate([length-edges,width-edges,edges]) sphere(edges);
            
            //outer lower sides
            translate([edges,edges,edges]) rotate([0,90,0]) cylinder(r = edges,h = length-2*edges);
            translate([edges,width-edges,edges]) rotate([0,90,0]) cylinder(r = edges,h = length-2*edges);    
            translate([edges,edges,edges]) rotate([-90,0,0]) cylinder(r = edges,h = width-2*edges);      
            translate([length-edges,edges,edges]) rotate([-90,0,0]) cylinder(r = edges,h = width-2*edges); 
            
            //bottom
            translate([edges,edges,0]) cube([length-2*edges,width-2*edges,thickness]);
            
            //outer upper sides
            translate([0,edges,edges]) cube([length,width-2*edges,height/2-edges]);
            translate([edges,0,edges]) cube([length-2*edges,width,height/2-edges]);
            
            //outer upper corners
            translate([edges,edges,edges]) cylinder(r = edges,h = height/2-edges); 
            translate([length-edges,edges,edges]) cylinder(r = edges,h = height/2-edges);
            translate([edges,width-edges,edges]) cylinder(r = edges,h = height/2-edges);
            translate([length-edges,width-edges,edges]) cylinder(r = edges,h = height/2-edges);
        }    
        union(){
            //inner lower coners
            translate([inneredges,inneredges,inneredges]) sphere(edges);
            translate([length-inneredges,inneredges,inneredges]) sphere(edges);
            translate([inneredges,width-inneredges,inneredges]) sphere(edges);    
            translate([length-inneredges,width-inneredges,inneredges]) sphere(edges);
            
            //inner lower sides
            translate([inneredges,inneredges,inneredges]) rotate([0,90,0]) cylinder(r = edges,h = length-2*inneredges);
            translate([inneredges,width-inneredges,inneredges]) rotate([0,90,0]) cylinder(r = edges,h = length-2*inneredges);    
            translate([inneredges,inneredges,inneredges]) rotate([-90,0,0]) cylinder(r = edges,h = width-2*inneredges);      
            translate([length-inneredges,inneredges,inneredges]) rotate([-90,0,0]) cylinder(r = edges,h = width-2*inneredges); 
            
            //inner bottom
           translate([edges,edges,thickness]) cube([length-2*edges,width-2*edges,height/2-thickness]);
            
            //inner upper sides
            translate([thickness,inneredges,inneredges]) cube([length-2*thickness,width-2*inneredges,height/2-inneredges]);
            translate([inneredges,thickness,inneredges]) cube([length-2*inneredges,width-2*thickness,height/2-inneredges]);
            
            //inner upper coners
            translate([inneredges,inneredges,inneredges]) cylinder(r = edges,h = height/2-inneredges); 
                translate([length-inneredges,inneredges,inneredges]) cylinder(r = edges,h = height/2-edges);
                translate([inneredges,width-inneredges,inneredges]) cylinder(r = edges,h = height/2-inneredges);
                translate([length-inneredges,width-inneredges,inneredges]) cylinder(r = edges,h = height/2-inneredges);
            
            
            //chain hole
            translate([length-edges,edges,0]) cylinder(r = 2, h = 5, centering = true);
        }
    }
    union(){
        union(){
            //lower pins
            translate([edges,width/2-holes,thickness]) cylinder(r = outerdia/2, h = batterythickness, centering = true);
            translate([edges,width/2+holes,thickness]) cylinder(r = outerdia/2, h = batterythickness, centering = true);
            translate([length-edges+thickness,width/2-holes,thickness]) cylinder(r = outerdia/2, h = batterythickness, centering = true);
            translate([length-edges+thickness,width/2+holes,thickness]) cylinder(r = outerdia/2, h = batterythickness, centering = true);
        }
        
        union(){
            //upper pins
            translate([edges,width/2-holes,thickness]) cylinder(r = innerdia/2, h = innerheight, centering = true);
            translate([edges,width/2+holes,thickness]) cylinder(r = innerdia/2, h = innerheight, centering = true);
            translate([length-edges+thickness,width/2-holes,thickness]) cylinder(r = innerdia/2, h = innerheight, centering = true);
            translate([length-edges+thickness,width/2+holes,thickness]) cylinder(r = innerdia/2, h = innerheight, centering = true);
        }
    }
}   

//upper body
translate([0,width+5,0]){
    union(){
        difference(){
            union(){
                //outer lower cornes
                translate([edges,edges,edges]) sphere(edges);
                translate([length-edges,edges,edges]) sphere(edges);
                translate([edges,width-edges,edges]) sphere(edges);    
                translate([length-edges,width-edges,edges]) sphere(edges);
                
                //outer lower sides
                translate([edges,edges,edges]) rotate([0,90,0]) cylinder(r = edges,h = length-2*edges);
                translate([edges,width-edges,edges]) rotate([0,90,0]) cylinder(r = edges,h = length-2*edges);    
                translate([edges,edges,edges]) rotate([-90,0,0]) cylinder(r = edges,h = width-2*edges);      
                translate([length-edges,edges,edges]) rotate([-90,0,0]) cylinder(r = edges,h = width-2*edges); 
                
                //bottom
                translate([edges,edges,0]) cube([length-2*edges,width-2*edges,thickness]);
                
                //outer upper sides
                translate([0,edges,edges]) cube([length,width-2*edges,height/2-edges]);
                translate([edges,0,edges]) cube([length-2*edges,width,height/2-edges]);
                
                //outer upper corners
                translate([edges,edges,edges]) cylinder(r = edges,h = height/2-edges); 
                translate([length-edges,edges,edges]) cylinder(r = edges,h = height/2-edges);
                translate([edges,width-edges,edges]) cylinder(r = edges,h = height/2-edges);
                translate([length-edges,width-edges,edges]) cylinder(r = edges,h = height/2-edges);
            }    
            union(){
                //inner lower coners
                translate([inneredges,inneredges,inneredges]) sphere(edges);
                translate([length-inneredges,inneredges,inneredges]) sphere(edges);
                translate([inneredges,width-inneredges,inneredges]) sphere(edges);    
                translate([length-inneredges,width-inneredges,inneredges]) sphere(edges);
                
                //inner lower sides
                translate([inneredges,inneredges,inneredges]) rotate([0,90,0]) cylinder(r = edges,h = length-2*inneredges);
                translate([inneredges,width-inneredges,inneredges]) rotate([0,90,0]) cylinder(r = edges,h = length-2*inneredges);    
                translate([inneredges,inneredges,inneredges]) rotate([-90,0,0]) cylinder(r = edges,h = width-2*inneredges);      
                translate([length-inneredges,inneredges,inneredges]) rotate([-90,0,0]) cylinder(r = edges,h = width-2*inneredges); 
                
                //inner bottom
               translate([edges,edges,thickness]) cube([length-2*edges,width-2*edges,height/2-thickness]);
                
                //inner upper sides
                translate([thickness,inneredges,inneredges]) cube([length-2*thickness,width-2*inneredges,height/2-inneredges]);
                translate([inneredges,thickness,inneredges]) cube([length-2*inneredges,width-2*thickness,height/2-inneredges]);
                
                //inner upper coners
                translate([inneredges,inneredges,inneredges]) cylinder(r = edges,h = height/2-inneredges); 
                translate([length-inneredges,inneredges,inneredges]) cylinder(r = edges,h = height/2-inneredges);
                translate([inneredges,width-inneredges,inneredges]) cylinder(r = edges,h = height/2-inneredges);
                    translate([length-inneredges,width-inneredges,inneredges]) cylinder(r = edges,h = height/2-inneredges);
                    
                //chain hole
                translate([length-edges,width-edges,0]) cylinder(r = 2, h = 5, centering = true);
                                       
                //USB hole
                translate([0,width/2-usbwidth/2,height/2-usbheight]) cube([usblength,usbwidth,usbheight]);  
                
                //active LED hole
                translate([edges+41,width/2-holes+3,0]) cylinder(r = 1.5, h = thickness, centering = true);
                
                //button hole
                translate([edges+30,width/2,0]) cylinder(r = 2, h = thickness, centering = true);
                
                //alarm LED hole
                translate([edges,width/2-5.5,0]) cylinder(r = 1.5, h = thickness+3, centering = true);
            }
        }
        difference(){
        union(){
            //lower pins
            translate([edges,width/2-holes,thickness]) cylinder(r = outerdia/2, h = batterythickness-pcbthickness, centering = true);
            translate([edges,width/2+holes,thickness]) cylinder(r = outerdia/2, h = batterythickness-pcbthickness, centering = true);
            translate([length-edges+thickness,width/2-holes,thickness]) cylinder(r = outerdia/2, h = batterythickness, centering = true);
            translate([length-edges+thickness,width/2+holes,thickness]) cylinder(r = outerdia/2, h = batterythickness, centering = true);
        }
        
        union(){
            //upper pins
            translate([edges,width/2-holes,thickness]) cylinder(r = innerdia/2, h = innerheight, centering = true);
            translate([edges,width/2+holes,thickness]) cylinder(r = innerdia/2, h = innerheight, centering = true);
            translate([length-edges+thickness,width/2-holes,thickness]) cylinder(r = innerdia/2, h = innerheight, centering = true);
            translate([length-edges+thickness,width/2+holes,thickness]) cylinder(r = innerdia/2, h = innerheight, centering = true);
        }
        }
    }   
}    
 
