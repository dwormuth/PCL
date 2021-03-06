var timerIsBusy=false;
function onTimerEvent (){
   timerIsBusy=false;
   console.writeln("Got timer event");
}


function INDIclient() {

 this.INDIServer = "";
 this.INDIPort   = 7624;
 this.INDI = null;

 this.HOME_RA=[0,0,0];
 this.HOME_DEC=[90,0,0];

 this.timer = new Timer();
 this.timer.singleShot=true;
 this.timer.onTimeout=onTimerEvent;

}


INDIclient.prototype.setServerHost = function(host){
  this.INDIServer = host;
}

INDIclient.prototype.setServerPort = function(port){
 this.INDIPort   = port;
}

INDIclient.prototype.startTimer = function(interval){
   this.timer.interval=interval;
   this.timer.start();
   timerIsBusy=true;
}

INDIclient.prototype.stopTimer = function(interval){
   this.timer.stop();
   timerIsBusy=false;
}

INDIclient.prototype.execute = function() {
  this.INDI.executeGlobal();
  if (this.INDI.INDI_ProcessFlag_DoAbort){
     this.disconnectServer();
     throw Error("Process aborted");
  }
}

INDIclient.prototype.connectServer = function(){

   if (!this.INDI)
      this.INDI = new INDIClient;
   this.INDI.INDI_ServerHostname = this.INDIServer;
   this.INDI.INDI_ServerPort   = this.INDIPort;
   this.INDI.INDI_ServerConnect=1;
   this.INDI.executeGlobal();

}

INDIclient.prototype.disconnectServer = function(){

   if (!this.INDI)
      this.INDI = new INDIClient;
   this.INDI.INDI_ServerConnect=0;
   this.INDI.executeGlobal();
}

INDIclient.prototype.dumpProperties = function(){
   console.writeln(  "property,                    property value" );
   console.writeln(  "============================================" );
   for (var i=0; i<this.INDI.INDI_Properties.length; ++i){
      if (this.INDI.INDI_Properties[i][0]!="")
         console.writeln(this.INDI.INDI_Properties[i]);
   }
   console.flush();
}

INDIclient.prototype.sendNewProperty = function(Property,PropertyType,Value){
   var newPropertyArray=[[Property,PropertyType,Value]];
   this.INDI.INDI_NewProperties = newPropertyArray;

   this.execute();

}



INDIclient.prototype.sendNewPropertyArray = function(newPropertyArray){

   this.INDI.INDI_NewProperties = newPropertyArray;
   this.execute();
}

INDIclient.prototype.registerInstance = function(){
   this.INDI.INDI_ServerCommand="REGISTER_INSTANCE";
   this.execute();
}

INDIclient.prototype.releaseInstance = function(){
   this.INDI.INDI_ServerCommand="RELEASE_INSTANCE";
   this.execute();
}

INDIclient.prototype.sendNewPropertyArrayAsynch = function(newPropertyArray){
   this.INDI.INDI_ServerCommand="SET_ASYNCH";
   this.INDI.INDI_NewProperties = newPropertyArray;
   this.execute();
}




INDIclient.prototype.Goto = function(RA,DEC){
   var numRA=RA[0]+RA[1]/60 + RA[2]/3600;
   var numDEC=DEC[0]+DEC[1]/60 + DEC[2]/3600;
   var propertyArray=[["/EQMod Mount/EQUATORIAL_EOD_COORD/RA","INDI_NUMBER",numRA.toString()],
                  ["/EQMod Mount/EQUATORIAL_EOD_COORD/DEC","INDI_NUMBER",numDEC.toString()]];

   this.sendNewPropertyArray(propertyArray);

}

INDIclient.prototype.ParkToHome = function(){
   this.Goto(this.HOME_RA,this.HOME_DEC);

   this.sendNewProperty("/EQMod Mount/TELESCOPE_PARK/PARK","INDI_SWITCH","ON");
}


INDIclient.prototype.CheckPropertyValue = function(propertyKey,propertyType,Value) {
   var propertyKeyArray;
   var propertyValueIsOK=false;

   for (var i=0;i<this.INDI.INDI_Properties.length; ++i){
      if (this.INDI.INDI_Properties[i][0] == propertyKey){
         if (propertyType=="INDI_NUMBER"){
            var valueNumberActual   = new Number(Value);
            var valueNumberExpected = new Number(this.INDI.INDI_Properties[i][1]);
            if (Math.abs(valueNumberExpected-valueNumberActual)<=0.0001){
               propertyValueIsOK=true;
               return propertyValueIsOK;
            }
            else {
                console.writeln("Property ",propertyKey," has not expected value ",  this.INDI.INDI_Properties[i][1] , " but ", Value );
                return propertyValueIsOK;
            }
         }
         else {
            if (this.INDI.INDI_Properties[i][1]==Value){
               propertyValueIsOK=true;
               return propertyValueIsOK;
            } else {
                console.writeln("Property ",propertyKey," has not expected value ", Value, " but ", this.INDI.INDI_Properties[i][1] );
                return propertyValueIsOK;
            }
         }
      }
   }
   return propertyValueIsOK;
}


INDIclient.prototype.CheckPropertyExists = function(propertyKey) {
   var propertyKeyArray;
   var propertyFound=false;
   if (this.INDI===null)
      return propertyFound;
   for (var i=0;i<this.INDI.INDI_Properties.length; ++i){
      if (this.INDI.INDI_Properties[i][0] == propertyKey){
         propertyFound=true;
         return propertyFound;
      }
   }
   if (!propertyFound){
      console.writeln("Property ",propertyKey," could not be found" );
   }
   return propertyFound;
}


INDIclient.prototype.getPropertyValue = function(propertyKey) {
   var propertyKeyArray;
   for (var i=0;i<this.INDI.INDI_Properties.length; ++i){
      if (this.INDI.INDI_Properties[i][0] == propertyKey){
         return this.INDI.INDI_Properties[i][1];
      }
   }
   console.writeln("Property ",propertyKey," could not be found" );
  return null;
}

INDIclient.prototype.getPropertyValue2 = function(propertyKey) {
   this.INDI.INDI_ServerCommand="GET";
   this.INDI.INDI_GetPropertyPropertyParam=propertyKey;
   this.INDI.executeGlobal();
   this.INDI.INDI_ServerCommand="";
   return this.INDI.INDI_GetPropertyReturnValue;
}

