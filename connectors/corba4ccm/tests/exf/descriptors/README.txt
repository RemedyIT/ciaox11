
This (fairly complex) test / example simulates an environmental monitoring system with sensors (Generator component) 
and monitors (Monitor component) generating data, an Aggregator component collecting and aggregating data, an Analyzer
component disseminating the aggregated data and presenting reports to a Reporter component.

The various deployment plans (in both CONFIG and CDP formats) showcase the various options ExF supports to organize
system deployments as well as the fact that component implementations are (in principle) not dependent on the ExF
infrastructure and (if designed and implemented keeping the NRE differences between non-ExF and ExF in mind) can be
deployed both with and without ExF support without changes or even recompilation.  

== plan

This plan deploys the system in a fairly default setup with 
- a node running a single locality without ExF support with 2 Generator components and 2 Monitor components
- a node running one locality with ExF support with an Aggregator component and one locality without ExF support 
  with an Analyzer component
- a node running one locality with ExF support with a Reporter component

== plan-no-exf

This plan deploys the system without any ExF support with
- a node running a single locality with 2 Generator components and 2 Monitor components
- a node running one locality with an Aggregator component and one locality with an Analyzer component
- a node running one locality with a Reporter component

== plan-full-exf

This plan deploys the system with full ExF support with
- a node running a single locality with ExF support with 2 Generator components and 2 Monitor components
- a node running one locality with ExF support with an Aggregator component and one locality with an Analyzer component
- a node running one locality with ExF support with a Reporter component

== plan-exf-and-non-exf-container

This plan showcases the possibility to have multiple componenent containers in the context of a single locality
and have some with and some without ExF support.
This plan deploys the system with
- a node running a single locality without ExF support with 2 Generator components and 2 Monitor components
- a node running a single locality with a default container with ExF support with an Aggregator component and one 
  additional container without ExF support with an Analyzer component
- a node running one locality with ExF support with a Reporter component

== plan-deadlines-and-delays

This plan showcases the deadline monitoring options of ExF.
The plan defines deadline monitoring options for the Aggregators data collection events and simulates collection delays
to make events exceed their deadlines.
This plan deploys the system with 
- a node running a single locality without ExF support with 2 Generator components and 2 Monitor components
- a node running one locality with ExF support with an Aggregator component and one locality without ExF support 
  with an Analyzer component
- a node running one locality with ExF support with a Reporter component

== plan-colocated

This plan shows the possibility to directly connect components in a colocated setup to circumvent possible ExF 
deadlocks in a default ExF setup.
The deadlocks are possible in case the default ExF locality setup is used which instantiates a single container 
with a non-exclusive, single threaded scheduling lane. If ExF connectors were used the Analyzer triggered on the 
ExF thread would attempt to send a request to the Aggregator which would deadlock as the (single) ExF thread is
blocked. Using direct component connections is one way to circumvent this problem in this situation.     
This plan deploys the system with
- a node running a single locality without ExF support with 2 Generator components and 2 Monitor components
- a node running a single locality with ExF support with a colocated Aggregator component and an Analyzer component
- a node running one locality with ExF support with a Reporter component

== plan-coloc-dynmt-lane

This plan shows another option to solve colocated connection issues as well as the possibility to reconfigure the
default ExF locality setup.
This plan sets up the locality running the Aggregator and Analyzer components to instantiate a default container
with a non-exclusive, dynamically managed, multithreaded scheduling lane with 2 to 5 threads.
This allows ExF connectors to be used for the colocated connection since the requests can be handled on separate
ExF threads (so no deadlocks).
This plan deploys the system with
- a node running a single locality without ExF support with 2 Generator components and 2 Monitor components
- a node running a single locality with ExF support (non-exclusive dynamically multithreaded) with a colocated 
  Aggregator component and an Analyzer component
- a node running one locality with ExF support with a Reporter component

== plan-coloc-exclusive-lane

This plan shows another option to solve colocated connection issues by being able to individually configure ExF
scheduling options for each Component.
This plan sets up the Aggregator component to use it's own exclusive scheduling lane apart from the default 
non-exclusive scheduling lane.
This way the Analyzer component will use the default scheduling lane (and it's thread) and a request to the 
Aggregator will be handled on it's own, separate, scheduling lane (and thread). 
This plan deploys the system with
- a node running a single locality without ExF support with 2 Generator components and 2 Monitor components
- a node running a single locality with ExF support with a colocated Aggregator component (with exclusive 
  scheduling lane) and an Analyzer component
- a node running one locality with ExF support with a Reporter component

== plan-coloc-mt-lane

This plan shows yet another option to solve colocated connection issues by using a multithreaded, grouped, 
scheduling lane for the Aggregator and Analyzer components.
This plan sets up the Aggregator and Analyzer components to use a scheduling lane for a named group with 2 threads
and assigns each component to the same group. 
This provides a similar solution to plan-coloc-dynmt-lane.
This plan deploys the system with
- a node running a single locality without ExF support with 2 Generator components and 2 Monitor components
- a node running a single locality with ExF support with a colocated Aggregator component and an Analyzer component
  both using a multithreaded (2) scheduling lane for group 'MTGroup'
- a node running one locality with ExF support with a Reporter component

== plan-2-aggregators

This plan shows options for scaling up the system with 2 Aggregator components.
The Aggregators are configured to use a separate, single threaded, grouped scheduling lane.
This plan deploys the system with
- a node running a single locality without ExF support with 2 Generator components and 2 Monitor components
- a node running one locality with ExF support with two Aggregator components and one locality without ExF 
  support with an Analyzer component
- a node running one locality with ExF support with a Reporter component
  