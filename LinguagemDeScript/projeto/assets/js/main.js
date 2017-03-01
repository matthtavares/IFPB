'use strict';

/// Mount a query string
Object.prototype.query = function(){
	let q = '';

	for(let k of Object.keys(this)){
		q += `&${k}=${this[k]}`;
	}

	return q.substr(1);
}

/// Get query params
window.$_GET = window.location.search.substr(1).split('&').reduce(function(o, i){
	let
		u = decodeURIComponent,
		[k, v] = i.split('=');

	o[u(k)] = v && u(v);

	return o;
}, {});

/// Execute all requisitions
function getJSON( url, callback ){
	let xhr = new XMLHttpRequest();
	xhr.onload = () => callback( JSON.parse(xhr.responseText) );
	xhr.open( 'GET', url );
	xhr.send();
}

/**
 * Functions to OMDb
 */

/// Load requisition
function searchOMDb(){
	let url = 'http://www.omdbapi.com/?';
	let params = {
		"s": $_GET['s'],
		"type": $_GET['type'],
		"r": "json",
		"page": (typeof $_GET['page'] != 'undefined') ? $_GET['page'] : 1
		//"plot": "short",
		//"tomatoes": true
	};
	url += params.query();
	getJSON( url, showSearchResults );
}

function showSearchResults( json ){
	let
		temp = '',
		i = 1;

	if( json.totalResults > 0 ){

		for(let value of json.Search){
			// Replace image if not avaible
			if( value.Poster == 'N/A' )
				value.Poster = 'https://placeholdit.imgix.net/~text?txtsize=18&txt=Poster+n%C3%A3o+dispon%C3%ADvel&w=250&h=360&txttrack=0';
			
	        if( i == 1 ){
	          temp += '<div class="row">';
	        }
	        temp += `<div class="col-md-3"><div class="thumbnail"><a href="film.html?imdb=${value.imdbID}"><img src="${value.Poster}" alt="${value.Title}"></a><div class="caption"><h2>${value.Title}</h2><p><b>Ano:</b> ${value.Year}<br><b>Tipo:</b> ${value.Type}<br><b>IMDb:</b> ${value.imdbID}</p></div></div></div>`;
	        if( i == 4 ){
	          temp += '</div>';
	          i = 0;
	        }
	        i++;
		}

		// Show pagination
		showSearchPagination(json.totalResults);

	} else {
		temp = '<h3 class="text-danger text-center">Não há resultados!</h3>';
	}

	document.getElementById('searchResults').innerHTML = temp;

	// Hide loading
	document.getElementById('loader').style.display = "none";
}

function showSearchPagination( totalResults ){
	let
		pag = '<nav><ul class="pagination">',
		url = window.location.href,
		currentPage = parseInt($_GET['page']),
		cssClass = '',
		totalPages = Math.ceil( totalResults / 10 );

	if( currentPage != 'undefined' )
		url = url.replace(/\&page\=(\d)+/g, '');

	/// First page
	if( currentPage == 1 )
		cssClass = ' class="disabled"';
	pag += `<li${cssClass}><a href="${url}&page=1"><i class="fa fa-angle-double-left"></i></a></li>`;

	/// Previous page
	if( currentPage == 1 )
		cssClass = ' class="disabled"';
	pag += `<li${cssClass}><a href="${url}&page=${currentPage - 1}"><i class="fa fa-angle-left"></i></a></li>`;

	for(let i = 1; i <= totalPages; i++){
		cssClass = (currentPage == i) ? ' class="active"' : '';
		pag += `<li${cssClass}><a href="${url}&page=${i}">${i}</a></li>`;
	}

	/// Next page
	if( currentPage == totalPages )
		cssClass = ' class="disabled"';
	pag += `<li${cssClass}><a href="${url}&page=${currentPage + 1}"><i class="fa fa-angle-right"></i></a></li>`;

	/// Last page
	if( currentPage == totalPages )
		cssClass = ' class="disabled"';
	pag += `<li${cssClass}><a href="${url}&page=${totalPages}"><i class="fa fa-angle-double-right"></i></a></li>`;

	pag += '</ul></nav>';

	document.getElementById('searchPagination').innerHTML = pag;
}

function getMovieData(){
	let url = 'http://www.omdbapi.com/?';
	let params = {
		"i": $_GET['imdb'],
		//"type": $_GET['type'],
		"r": "json",
		//"page": (typeof $_GET['page'] != 'undefined') ? $_GET['page'] : 1,
		"plot": "full",
		"tomatoes": true
	};
	url += params.query();
	getJSON( url, showMovieData );
}

function showMovieData( json ){
	let
		$filmTitle = document.querySelector('.film-title'),
		$filmYear = document.querySelector('.film-year'),
		$filmImdb = document.querySelector('.film-imdb'),
		$filmActors = document.querySelector('.film-actors'),
		$filmPoster = document.querySelector('.film-poster'),
		$filmPlot = document.querySelector('.film-plot');

	$filmTitle.innerHTML = json.Title;
	$filmYear.innerHTML = json.Year;
	$filmImdb.innerHTML = json.imdbID;
	$filmActors.innerHTML = json.Actors;
	$filmPlot.innerHTML = json.Plot;
	$filmPoster.setAttribute('src', json.Poster);
	$filmPoster.setAttribute('alt', json.Title);

	getMovieTorrents();
}

function getMovieTorrents(){
	let url = 'torrentapi.php?';
	let params = {
		"mode": "search",
		"format": "json",
		"search_imdb": $_GET['imdb']
	};
	url += params.query();
	getJSON( url, showTorrentList );
}

function showTorrentList( json ){
	let temp = '';

	for(let value of json){
		temp += `<tr><td>${value.filename}</td><td><a href="${value.download}" target="_blank">Baixar</a></td></tr>`;
	}

	document.querySelector('#tableTorrent tbody').innerHTML = temp;
	document.getElementById('loader').style.display = "none";
}