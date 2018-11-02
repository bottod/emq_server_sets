/***************************************************/
/*for echarts test*/
function set_test(id,theme)
{
	var myChart = echarts.init(document.getElementById(id),theme);

        var option = {
        title : {
            text: '未来一周气温变化',
            subtext: '纯属虚构'
        },
        tooltip : {
            trigger: 'axis'
        },
        legend: {
            data:['最高气温','最低气温']
        },
        toolbox: {
            show : true,
            feature : {
                mark : {show: true},
                dataView : {show: true, readOnly: false},
                magicType : {show: true, type: ['line', 'bar']},
                restore : {show: true},
                saveAsImage : {show: true}
            }
        },
        calculable : true,
        xAxis : [
            {
                type : 'category',
                boundaryGap : false,
                data : ['周一','周二','周三','周四','周五','周六','周日']
            }
        ],
        yAxis : [
            {
                type : 'value',
                axisLabel : {
                    formatter: '{value} °C'
                }
            }
        ],
        series : [
            {
                name:'最高气温',
                type:'line',
                data:[11, 11, 15, 13, 12, 13, 10],
                markPoint : {
                    data : [
                        {type : 'max', name: '最大值'},
                        {type : 'min', name: '最小值'}
                    ]
                },
                markLine : {
                    data : [
                        {type : 'average', name: '平均值'}
                    ]
                },
                label: {
                      normal: {
                          show: true,
                          position: 'top',
                          textStyle: {
                            color: 'white'
                          }
                      }
                 }
            },
            {
                name:'最低气温',
                type:'line',
                data:[1, -2, 2, 5, 3, 2, 0],
                markPoint : {
                    data : [
                        {name : '周最低', value : -2, xAxis: 1, yAxis: -1.5}
                    ]
                },
                markLine : {
                    data : [
                        {type : 'average', name : '平均值'}
                    ]
                }
            }
        ]
        };  
    myChart.setOption(option);
}
/***************************************************/



/***********************************************************/
/*one data*/
function set_last_response_time(htmlid,clientid)
{
    $.ajax
    ({
      type : "post",
      async : true,
      url : "./php/get_last_data.php?id=" + clientid,
      data : {},
      dataType : "json",
      success : function(result)
      {
        if (result) 
            document.getElementById(htmlid).innerHTML = result.time;
        else
            document.getElementById(htmlid).innerHTML = "nil";
      }
    })
}

function set_last_temperature(htmlid,clientid)
{
    $.ajax
    ({
      type : "post",
      async : true,
      url : "./php/get_last_data.php?id=" + clientid,
      data : {},
      dataType : "json",
      success : function(result)
      {
        if (result) 
            document.getElementById(htmlid).innerHTML = result.tmp;
        else
            document.getElementById(htmlid).innerHTML = "nil";
      }
    })
}

function set_last_voltage(htmlid,clientid)
{
    $.ajax
    ({
      type : "post",
      async : true,
      url : "./php/get_last_data.php?id=" + clientid,
      data : {},
      dataType : "json",
      success : function(result)
      {
        if (result) 
            document.getElementById(htmlid).innerHTML = result.vol;
        else
            document.getElementById(htmlid).innerHTML = "nil";
      }
    })
}

function set_last_humidity(htmlid,clientid)
{
    $.ajax
    ({
      type : "post",
      async : true,
      url : "./php/get_last_data.php?id=" + clientid,
      data : {},
      dataType : "json",
      success : function(result)
      {
        if (result) 
            document.getElementById(htmlid).innerHTML = result.hum;
        else
            document.getElementById(htmlid).innerHTML = "nil";
      }
    })
}
/************************************************************/




/**********************************************************/
/*for one page dom*/
var timer;
function load_all_page(clientid)
{
    one_page_action(clientid)
    if(timer)
        clearInterval(timer);
    timer = setInterval(one_page_action,60000,clientid);
}

function one_page_action(clientid)
{
    set_response_time_graph_async("response_time_graph","dark",clientid);
    set_voltage_graph_async("voltage_graph","dark",clientid);
    set_temperature_graph_async("temperature_graph","dark",clientid);
    set_humidity_graph_async("humidity_graph","dark",clientid); 
    set_last_response_time("response_time_count",clientid);
    set_last_temperature("voltage_count",clientid);
    set_last_voltage("temperature_count",clientid);
    set_last_humidity("humidity_count",clientid);
}
/**********************************************************/





/**********************************************************/
/*auto detect sql table and add li*/
function auto_add_client(htmlid)
{
    var xhr = new XMLHttpRequest;
    xhr.open('post', './php/get_table.php');
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.send();
    xhr.onreadystatechange = function() 
    {
        if(xhr.readyState == 4 && (xhr.status == 200 || xhr.status ==304)) 
        { 
            var rst = JSON.parse(xhr.responseText);
            for(i=0;i<rst.length;i++)
            {
                var ul = document.getElementById(htmlid);
                var li = document.createElement("li");
                li.innerHTML="<a href=\"javascript:void(0);\" onclick=load_all_page(\""+rst[i]+"\")>"+rst[i]+"</a>";
                ul.appendChild(li);
            }
            load_all_page(rst[0]);
        }
    }
}
/**********************************************************/




/***************************** async ***********************************/
/*async mode set graph*/
function set_temperature_graph_async(htmlid,theme,clientid)
{
    echarts.dispose(document.getElementById(htmlid));
    var myChart = echarts.init(document.getElementById(htmlid),theme);

    myChart.showLoading();

    var arr_tmp=[],arr_ctime=[];
    $.ajax
    ({
        type : "post",
        async : true,
        url : "./php/get_data.php?id=" + clientid,
        data : {},
        dataType : "json",
        success : function(result)
        {
            if (result) 
            {
                for (var i = 0; i < result.length; i++) 
                {
                    arr_tmp.push(result[i].tmp);
                    arr_ctime.push(result[i].ctime);
                }
                myChart.hideLoading();

                var option = 
                {
                    title : 
                    {
                        text: '温度数据',
                        subtext: '@jack'
                    },
                    tooltip : 
                    {
                        trigger: 'axis'
                    },
                    legend : 
                    {
                        data:['土壤温度']
                    },
                    toolbox : 
                    {
                        show : true,
                        feature : 
                        {
                            mark : { show: true },
                            dataView : { show: true, readOnly: false },
                            magicType : { show: true, type: ['line', 'bar'] },
                            restore : { show: true },
                            saveAsImage : { show: true }
                        }
                    },
                    calculable : true,
                    xAxis: 
                    {
                        type: 'category',
                        data: arr_ctime
                    },
                    yAxis: 
                    {
                        type: 'value'
                    },
                    series: 
                    [{
                        name: '土壤温度',
                        type: 'line',
                        data: arr_tmp,
                        label: 
                        {
                            normal: 
                            {
                                show: true,
                                position: 'top',
                                textStyle: 
                                {
                                    color: 'white'
                                }
                            }
                        }
                    }]
                };

                myChart.setOption(option);

            }
        },
        error : function(errorMsg) 
        {
            alert("图表请求数据失败!");
            myChart.hideLoading();
        }
    })
}

function set_response_time_graph_async(htmlid,theme,clientid)
{
    echarts.dispose(document.getElementById(htmlid));
    var myChart = echarts.init(document.getElementById(htmlid),theme);

    myChart.showLoading();

    var arr_time=[],arr_ctime=[];
    $.ajax
    ({
        type : "post",
        async : true,
        url : "./php/get_data.php?id=" + clientid,
        data : {},
        dataType : "json",
        success : function(result)
        {
            if (result) 
            {
                for (var i = 0; i < result.length; i++) 
                {
                    arr_time.push(result[i].time);
                    arr_ctime.push(result[i].ctime);
                }
                myChart.hideLoading();

                var option = 
                {
                    title : 
                    {
                        text: '时间数据',
                        subtext: '@jack'
                    },
                    tooltip : 
                    {
                        trigger: 'axis'
                    },
                    legend : 
                    {
                        data:['响应时间']
                    },
                    toolbox : 
                    {
                        show : true,
                        feature : 
                        {
                            mark : { show: true },
                            dataView : { show: true, readOnly: false },
                            magicType : { show: true, type: ['line', 'bar'] },
                            restore : { show: true },
                            saveAsImage : { show: true }
                        }
                    },
                    calculable : true,
                    xAxis: 
                    {
                        type: 'category',
                        data: arr_ctime
                    },
                    yAxis: 
                    {
                        type: 'value'
                    },
                    series: 
                    [{
                        name: '响应时间',
                        type: 'line',
                        data: arr_time,
                        label: 
                        {
                            normal: 
                            {
                                show: true,
                                position: 'top',
                                textStyle: 
                                {
                                    color: 'white'
                                }
                            }
                        }
                    }]
                };

                myChart.setOption(option);

            }
        },
        error : function(errorMsg) 
        {
            alert("图表请求数据失败!");
            myChart.hideLoading();
        }
    })
}

function set_humidity_graph_async(htmlid,theme,clientid)
{
    echarts.dispose(document.getElementById(htmlid));
    var myChart = echarts.init(document.getElementById(htmlid),theme);

    myChart.showLoading();

    var arr_hum=[],arr_ctime=[];
    $.ajax
    ({
        type : "post",
        async : true,
        url : "./php/get_data.php?id=" + clientid,
        data : {},
        dataType : "json",
        success : function(result)
        {
            if (result) 
            {
                for (var i = 0; i < result.length; i++) 
                {
                    arr_hum.push(result[i].hum);
                    arr_ctime.push(result[i].ctime);
                }
                myChart.hideLoading();
                
                var option = 
                {
                    title : 
                    {
                        text: '湿度数据',
                        subtext: '@jack'
                    },
                    tooltip : 
                    {
                        trigger: 'axis'
                    },
                    legend : 
                    {
                        data:['土壤湿度']
                    },
                    toolbox : 
                    {
                        show : true,
                        feature : 
                        {
                            mark : { show: true },
                            dataView : { show: true, readOnly: false },
                            magicType : { show: true, type: ['line', 'bar'] },
                            restore : { show: true },
                            saveAsImage : { show: true }
                        }
                    },
                    calculable : true,
                    xAxis: 
                    {
                        type: 'category',
                        data: arr_ctime
                    },
                    yAxis: 
                    {
                        type: 'value'
                    },
                    series: 
                    [{
                        name: '土壤湿度',
                        type: 'line',
                        data: arr_hum,
                        label: 
                        {
                            normal: 
                            {
                                show: true,
                                position: 'top',
                                textStyle: 
                                {
                                    color: 'white'
                                }
                            }
                        }
                    }]
                };

                myChart.setOption(option);

            }
        },
        error : function(errorMsg) 
        {
            alert("图表请求数据失败!");
            myChart.hideLoading();
        }
    })
}

function set_voltage_graph_async(htmlid,theme,clientid)
{
    echarts.dispose(document.getElementById(htmlid));
    var myChart = echarts.init(document.getElementById(htmlid),theme);

    myChart.showLoading();

    var arr_vol=[],arr_ctime=[];
    $.ajax
    ({
        type : "post",
        async : true,
        url : "./php/get_data.php?id=" + clientid,
        data : {},
        dataType : "json",
        success : function(result)
        {
            if (result) 
            {
                for (var i = 0; i < result.length; i++) 
                {
                    arr_vol.push(result[i].vol);
                    arr_ctime.push(result[i].ctime);
                }
                myChart.hideLoading();
                
                var option = 
                {
                    title : 
                    {
                        text: '电压数据',
                        subtext: '@jack'
                    },
                    tooltip : 
                    {
                        trigger: 'axis'
                    },
                    legend : 
                    {
                        data:['电池电压']
                    },
                    toolbox : 
                    {
                        show : true,
                        feature : 
                        {
                            mark : { show: true },
                            dataView : { show: true, readOnly: false },
                            magicType : { show: true, type: ['line', 'bar'] },
                            restore : { show: true },
                            saveAsImage : { show: true }
                        }
                    },
                    calculable : true,
                    xAxis: 
                    {
                        type: 'category',
                        data: arr_ctime
                    },
                    yAxis: 
                    {
                        type: 'value'
                    },
                    series: 
                    [{
                        name: '电池电压',
                        type: 'line',
                        data: arr_vol,
                        label: 
                        {
                            normal: 
                            {
                                show: true,
                                position: 'top',
                                textStyle: 
                                {
                                    color: 'white'
                                }
                            }
                        }
                    }]
                };

                myChart.setOption(option);

            }
        },
        error : function(errorMsg) 
        {
            alert("图表请求数据失败!");
            myChart.hideLoading();
        }
    })
}
/**********************************************************/