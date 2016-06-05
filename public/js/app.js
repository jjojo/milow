var robotApp = angular.module('robotApp', ["ngRoute",'ngResource','ui.bootstrap']);

robotApp.config(['$routeProvider',
  function($routeProvider) {
    $routeProvider.
      when('/', {                        
        templateUrl: 'partials/home.html',
        controller: 'HomeCtrl'
      }).
      otherwise({
        redirectTo: '/'
      });
}]);
