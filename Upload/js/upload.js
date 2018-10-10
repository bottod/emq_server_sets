/*
	1. If we use "reader.readAsBinaryString(file);" to replace "reader.readAsArrayBuffer(file);"  we can just use "reader.result"
        to get string. But in MDN. it is nonstandard and MDN recommend we to use the second one. and if we use first one ,the char
        code is not utf-8
*/

//ArrayBuffer To String
function ArrBuf2Str(buffer,func) 
{
	var blob = new Blob([buffer]);
	var reader = new FileReader();
	reader.readAsText(blob, 'utf-8');
	reader.onload = function(){if(func)func.call(null,reader.result)}
}

//String To ArrayBuffer
function Str2ArrBuf(str,func) 
{
	var blob = new Blob([s],{type:'text/plain'});
	var reader = new FileReader();
	reader.readAsArrayBuffer(blob);
	reader.onload = function(){if(func)func.call(null,reader.result)}
}

function uploadAndSubmit()
{
	//find a form (whatever id or name)
    var form = document.forms["UploadForm"];  
    // search in form to find label which Like <input type="file" name/id = "file' /> 
    if (form["file"].files.length > 0) 
    { 
        var file = form["file"].files[0];  //first form
        
        var reader = new FileReader();
        //triggered when load start 
        reader.onloadstart = function() 
        { 
            document.getElementById("bytesTotal").textContent = file.size; 
        }

        //loop triggered when loading
        reader.onprogress = function(p) 
        { 
            document.getElementById("bytesRead").textContent = p.loaded; 
        } 

        //triggered when loaded finish succeed
        reader.onload = function() 
        { 
			var str = null; ArrBuf2Str(reader.result,function(str)
            {
                //var xhr = new XMLHttpRequest();
                //xhr.open("POST", "../php/upload.php?fileName=" + file.name ,true);
                //xhr.overrideMimeType("application/octet-stream");
                //xhr.sendAsBinary(str);
                //xhr.onreadystatechange = function()
                //{
                //    if (xhr.readyState == 4) //loaded
                //    {
                //        if (xhr.status == 200) //ok
                //        {
                //            console.log("upload complete");
                //            console.log("response: " + xhr.responseText);
                //        }
                //   }
                // }
                console.log(str);
            });
        } 

        //triggered whenever loaded finish succeed or failed
        reader.onloadend = function() 
        { 
            if (reader.error) 
            { 
                console.log(reader.error); 
            } 
            else 
            { 
                document.getElementById("bytesRead").textContent = file.size; 
                console.log("load succeed");
                
                var xhr = new XMLHttpRequest(); 
                xhr.open("POST", "../php/upload.php?fileName=" + file.name ,true); 
                xhr.overrideMimeType("application/octet-stream"); 
                xhr.send(reader.result); 
                xhr.onreadystatechange = function() 
                { 
                    if (xhr.readyState == 4) //loaded
                    { 
                        if (xhr.status == 200) //ok
                        { 
                            console.log("upload complete"); 
                            console.log("response: " + xhr.responseText); 
                        } 
                    } 
                }
            }
        } 
        reader.readAsArrayBuffer(file);
    } 
    else
    { 
        alert ("Please Choose A File."); 
    } 

    if(!XMLHttpRequest.prototype.sendAsBinary)
    {
	    XMLHttpRequest.prototype.sendAsBinary = function(datastr) 
        {
		    function byteValue(x) 
            {
		        return x.charCodeAt(0) & 0xff;
		    }
		    var ords = Array.prototype.map.call(datastr, byteValue);
		    var ui8a = new Uint8Array(ords);
		    this.send(ui8a.buffer);
		};
	}

}
