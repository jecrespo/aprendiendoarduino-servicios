$(function () {			
    $(document).ready(function() {
		Highcharts.setOptions({
			global: {
				useUTC: false
			}
        });
		var options = {
			chart: {
                type: 'spline',
				zoomType: 'x',
				marginBottom: 40,
				backgroundColor: {
					linearGradient: [0, 0, 0, 100],
					stops: [
						[0, 'rgb(96, 96, 96)'],
						[1, 'rgb(0, 0, 0)']
					]
				},
				borderRadius: 15,
				events: {
					load: function() {
						var series1 = this.series[0];
						setInterval(function(){
							jQuery.get('./scripts/get_last_data.php', 'arduino=19', function(tsv) {
								var lines = [],
								tsv = tsv.split(":");
								var x =tsv[0]*1000;
								y1=parseFloat(tsv[1].replace(',', '.'));
								series1.addPoint([x,y1],true,true);
							})
						},5000);
					}
				}
            },
            title: {
				x: 20,
				style: {
					color: '#FFF',
					font: '16px Lucida Grande, Lucida Sans Unicode, Verdana, Arial, Helvetica, sans-serif'
				}
			},
			xAxis: {
                gridLineWidth: 0,
				lineColor: '#999',
				tickColor: '#999',
				type: 'datetime',
				labels: {
					style: {
						color: '#999',
						fontWeight: 'bold'
					},
					rotation: -35,
					x: -10,
					y: 25,
					align: 'center',
				}
            },
            yAxis: {
				alternateGridColor: 'rgba(68, 170, 213, .3)',
				minorTickInterval: null,
				gridLineWidth: 1,				
				gridLineColor: 'rgba(255, 255, 255, .2)',
				tickInterval: 2,
				labels: {
					style: {
						color: '#999',
						fontWeight: 'bold'
					},
					formatter: function() {
                        return this.value +' C'
                    }
				},
				title: {
					style: {
						color: '#AAA',
						font: 'bold 12px Lucida Grande, Lucida Sans Unicode, Verdana, Arial, Helvetica, sans-serif'
					},
					text: 'Temperatura (C)'
				},
				plotLines: [{
					dashStyle: 'ShortDash',
					width: 2,
					color: 'red',	//c1
				}]
			},
			tooltip: {	//Ventana emergente
				backgroundColor: '#FFF',
				borderWidth: 2,
				formatter: function() {
					return '<b>'+ this.series.name +'</b><br/>'+
					Highcharts.numberFormat(this.y, 2)+' C<br/>'+
					Highcharts.dateFormat('%H:%M:%S', this.x);
				}	
			},
			labels: {
				style: {
					color: '#CCC'
				}
			},
			legend: {
				enabled: false
			},
			toolbar: {
				itemStyle: {
					color: '#CCC'
				}
			},
			navigation: {
				buttonOptions: {
					backgroundColor: {
						linearGradient: [0, 0, 0, 20],
						stops: [
							[0.4, '#606060'],
							[0.6, '#333333']
						]
					},
					borderColor: '#000000',
					symbolStroke: '#C0C0C0',
					hoverSymbolStroke: '#FFFFFF'
				}
			},			
			plotOptions: {
				spline: {
					marker: {
						enabled: false,
						states: {
							hover: {
								enabled: true
							}
						}
					}
				},
				pointInterval: 6000
			},
			series: [{}]
        };
		
		jQuery.get('./scripts/get_data.php', 'arduino=19' , function(tsv, state, xhr) {
            var lines = [],
                date,
                sonda1 = [],
				tsv = tsv.split(";");
			jQuery.each(tsv, function(i, line) {
                line = line.split(":");
				date =(line[0]*1000);
				if (date>0) {
					y1=parseFloat(line[1].replace(',', '.'));
					sonda1.push([ date,	y1 ]);
				}
            });
			ind = 0;
            options.title.text = "Arduino 19";
            options.chart.renderTo = "arduino19";
            options.series[0].name = "Temperatura";
        	options.series[0].data = sonda1;
			options.series[0].color = "#FE3600";
            chart = new Highcharts.Chart(options);
        });
		
    });
});