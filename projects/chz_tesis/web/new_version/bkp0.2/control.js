window.onload = loop;

var data_received = 0;

function loop1(){
setTimeout(alertFunc(), 2000);
}

function alertFunc (){
alert("hola");
}

function loop() {
	if( !data_received )
		makeRequest("ajax.shtml");
	setTimeout("loop()",2000);
	//var d = new Date();
	//var n = d.getSeconds(); 
        //n=n.replace(".",",");
	//signal_ctrl(n%6);
	//battery_state(n%6);
        //temp_arrow(n,18,16);

}

function makeRequest(url){
  var http_request = false;
  data_received = 1;

  if (window.XMLHttpRequest){
    http_request = new XMLHttpRequest();
    if (http_request.overrideMimeType){
      http_request.overrideMimeType('text/xml');
    }
  }

  if(!http_request){
    alert('Giving up :( Cannot create an XMLHTTP instance');
    return false;
  }
  http_request.onreadystatechange = function() { alertContents(http_request); };
  http_request.open('GET', url, true);
  http_request.send(null);
}

function alertContents(http_request){

  if (http_request.readyState == 4){
    if (http_request.status == 200){
      update_values(http_request.responseText);
     //document.getElementById("sensor1").innerHTML = http_request.responseText;
      data_received = 0;
    }
    else{
      alert("There was a problem with the AJAX request.\n\r \
           Request status = " + http_request.status );
    }
  }
}


function update_values( data ){
 	var parsed = data.split('\n')
	for ( i = 0 ; i < parsed.length-1 ; i++) { 
		var argument=parsed[i].replace(/[#<!-]/g,"");
		var tag=argument.split('>');
		switch(tag[0]){
			case "alm0": //Set temperature Alarm
            	                document.getElementById("alarm").innerHTML = tag[1];
                                break;
			case "Tmax": //Set temperature Max
            	                document.getElementById("therm_max").innerHTML = tag[1];
                                break;
			case "Tmin": //Set temperature Min
            	                document.getElementById("therm_min").innerHTML = tag[1];
                                break;
			case "act0": case "act1": case "act2": case "act3" :	
				contacts_update(tag[1],tag[0]);
				break;
			case "sen0": // Temperature value, complit max and min
				temp_arrow(tag[1],15,17);
				break;
			case "sen1": // battery
				battery_state(tag[1]);
				break;
			case "sen2": // signal cel
				signal_modem(tag[1]);
				break;
			default :
				//console.log(tag[0]);
				break;
	  }

	}
}

function strCompare(str1,str2) {

	var n = str1.localeCompare(str2);
	return n;
}



function testAJAX()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (xhttp.readyState == 4 && xhttp.status == 200) {
            document.getElementById("sensor1").innerHTML = xhttp.responseText;
        }
    };
    xhttp.open("GET", "ajax.txt", true);
    xhttp.send();

}

function changebuttonClasses(elem) {
  if ( elem.className.match(/(?:^|\s)active(?!\S)/) )
    return;
  else {
    document.getElementById("menu1").className = document.getElementById("menu1").className.replace ( /(?:^|\s)active(?!\S)/g , '' );
    document.getElementById("menu2").className = document.getElementById("menu2").className.replace ( /(?:^|\s)active(?!\S)/g , '' );
    document.getElementById("menu3").className = document.getElementById("menu3").className.replace ( /(?:^|\s)active(?!\S)/g , '' );
    elem.className = "active";
  }
}

function signal_modem(signal){
	switch(signal){
case "1":
	document.getElementById("sig1_gprs").style.visibility='visible'
	document.getElementById("sig2_gprs").style.visibility='hidden'
	document.getElementById("sig3_gprs").style.visibility='hidden'
	document.getElementById("sig4_gprs").style.visibility='hidden'
	break;
case "2":
	document.getElementById("sig1_gprs").style.visibility='visible'
	document.getElementById("sig2_gprs").style.visibility='visible'
	document.getElementById("sig3_gprs").style.visibility='hidden'
	document.getElementById("sig4_gprs").style.visibility='hidden'
	break;
case "3":
	document.getElementById("sig1_gprs").style.visibility='visible'
	document.getElementById("sig2_gprs").style.visibility='visible'
	document.getElementById("sig3_gprs").style.visibility='visible'
	document.getElementById("sig4_gprs").style.visibility='hidden'
	break;
case "4":
	document.getElementById("sig1_gprs").style.visibility='visible'
	document.getElementById("sig2_gprs").style.visibility='visible'
	document.getElementById("sig3_gprs").style.visibility='visible'
	document.getElementById("sig4_gprs").style.visibility='visible'
	break;
default:
	document.getElementById("sig1_gprs").style.visibility='hidden'
	document.getElementById("sig2_gprs").style.visibility='hidden'
	document.getElementById("sig3_gprs").style.visibility='hidden'
	document.getElementById("sig4_gprs").style.visibility='hidden'
	break;
	}
}



function contacts_update(state,actuador){
	if ( state == "ON" ) {
		document.getElementById(actuador).style.fill='green'
  		document.getElementById(actuador+"_text").innerHTML = "ON";
	}else {
		document.getElementById(actuador).style.fill='red'
  		document.getElementById(actuador+"_text").innerHTML = "OFF";
	}
}



function battery_state(level){
	switch(level){
case "0":
	document.getElementById("batt0").style.visibility='hidden'
	document.getElementById("batt1").style.visibility='hidden'
	document.getElementById("batt2").style.visibility='hidden'
	document.getElementById("batt3").style.visibility='hidden'
	document.getElementById("batt4").style.visibility='hidden'
	document.getElementById("ray").style.visibility='hidden'
	break;
case "1":
	document.getElementById("batt0").style.visibility='visible'
	document.getElementById("batt1").style.visibility='hidden'
	document.getElementById("batt2").style.visibility='hidden'
	document.getElementById("batt3").style.visibility='hidden'
	document.getElementById("batt4").style.visibility='hidden'
	document.getElementById("ray").style.visibility='hidden'
	break;
case "2":
	document.getElementById("batt0").style.visibility='visible'
	document.getElementById("batt1").style.visibility='visible'
	document.getElementById("batt2").style.visibility='hidden'
	document.getElementById("batt3").style.visibility='hidden'
	document.getElementById("batt4").style.visibility='hidden'
	document.getElementById("ray").style.visibility='hidden'
	break;
case "3":
	document.getElementById("batt0").style.visibility='visible'
	document.getElementById("batt1").style.visibility='visible'
	document.getElementById("batt2").style.visibility='visible'
	document.getElementById("batt3").style.visibility='hidden'
	document.getElementById("batt4").style.visibility='hidden'
	document.getElementById("ray").style.visibility='hidden'
	break;
case "4":
	document.getElementById("batt0").style.visibility='visible'
	document.getElementById("batt1").style.visibility='visible'
	document.getElementById("batt2").style.visibility='visible'
	document.getElementById("batt3").style.visibility='visible'
	document.getElementById("batt4").style.visibility='hidden'
	document.getElementById("ray").style.visibility='hidden'
	break;
case "5":
	document.getElementById("batt0").style.visibility='visible'
	document.getElementById("batt1").style.visibility='visible'
	document.getElementById("batt2").style.visibility='visible'
	document.getElementById("batt3").style.visibility='visible'
	document.getElementById("batt4").style.visibility='visible'
	document.getElementById("ray").style.visibility='visible'
	break;
default:
	document.getElementById("batt0").style.visibility='hidden'
	document.getElementById("batt1").style.visibility='hidden'
	document.getElementById("batt2").style.visibility='hidden'
	document.getElementById("batt3").style.visibility='hidden'
	document.getElementById("batt4").style.visibility='hidden'
	document.getElementById("ray").style.visibility='hidden'
	break;
	}
}

function temp_arrow(temp){
  var domElement = document.getElementById('arrow_temp');   
	if(domElement){	
		/* graphics details 
		max thermometer pixel = 30
		max temp pixel = 90
		min temp pixel = 161
		(max - min) pixel = -71	
		(max + min ) pixel = 125.5
		min thermometer pixel = 200
		center temperature pixel = 125.5
		*/	
		var MAX_TEMP_PIXEL = 30;
		var MIN_TEMP_PIXEL = 220;

            	var max=document.getElementById("therm_max").innerHTML;
            	var min=document.getElementById("therm_min").innerHTML;
		m = -71  / (max-min) ;
		b = 125.5 - m*(max*1+min*1)/2;
		mv_arrow = b  + m*temp  ;
		
		if ( mv_arrow < MAX_TEMP_PIXEL ){
  			var move = 'translate(' + 130 + ',' + MAX_TEMP_PIXEL + ' )';  
		}else if ( mv_arrow > MIN_TEMP_PIXEL ){
  			var move = 'translate(' + 130 + ',' + MIN_TEMP_PIXEL + ' )';  
		} else {
  			var move = 'translate(' + 130 + ',' + mv_arrow + ' )';  
		}
		domElement.setAttribute('transform', move);
            	document.getElementById("tmp_value").innerHTML = temp;
	}
	
}

