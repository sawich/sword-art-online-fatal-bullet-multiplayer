#pragma once

namespace uef
{
	enum e_lifetime_condition
	{
		/** This property has no condition, and will send anytime it changes. **/
		COND_None = 0,

		/** This property will only attempt to send on the initial bunch. **/
		COND_InitialOnly = 1,

		/** This property will only send to the actor's owner. **/
		COND_OwnerOnly = 2,

		/** This property send to every connection EXCEPT the owner. **/
		COND_SkipOwner = 3,

		/** This property will only send to simulated actors. **/
		COND_SimulatedOnly = 4,

		/** This property will only send to autonomous actors. **/
		COND_AutonomousOnly = 5,

		/** This property will send to simulated OR bRepPhysics actors. **/
		COND_SimulatedOrPhysics = 6,

		/** This property will send on the initial packet, or to the actors owner. **/
		COND_InitialOrOwner = 7,

		/** This property has no particular condition, but wants the ability to toggle on/off via SetCustomIsActiveOverride. **/
		COND_Custom = 8,

		/** This property will only send to the replay connection, or to the actors owner. **/
		COND_ReplayOrOwner = 9,

		/** This property will only send to the replay connection. **/
		COND_ReplayOnly = 10,

		/** This property will send to actors only, but not to replay connections. **/
		COND_SimulatedOnlyNoReplay = 11,

		/** This property will send to simulated Or bRepPhysics actors, but not to replay connections. **/
		COND_SimulatedOrPhysicsNoReplay = 12,

		/** This property will not send to the replay connection. **/
		COND_SkipReplay = 13,

		/** Hidden **/
		COND_Max = 14
	};
}