
#include <iostream>
#include <list>

//behavior tree structure nodes 

class Node {  // This class represents each node in the behaviour tree.
	public:
		virtual bool run() = 0;
};

class CompositeNode : public Node {  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
	private:
		std::list<Node*> children;
	public:
		const std::list<Node*>& getChildren() const {return children;}
		void addChild (Node* child) {children.emplace_back(child);}
};

class Selector : public CompositeNode {
	public:
		virtual bool run() override {
			for (Node* child : getChildren()) {  // The generic Selector implementation
				if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
					return true;
			}
			return false;  // All children failed so the entire run() operation fails.
		}
};

class Sequence : public CompositeNode {
	public:
		virtual bool run() override {
			for (Node* child : getChildren()) {  // The generic Sequence implementation.
				if (!child->run())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
					return false;
			}
			return true;  // All children suceeded, so the entire run() operation succeeds.
		}
};

class DecoratorNode : public Node {  // Function is either to transform the result it receives from its child node's status, to terminate the child, or repeat processing of the child, depending on the type of decorator node.
			private:
				Node* child;  // Only one child allowed
			protected:
				Node* getChild() const {return child;}
			public:
				void setChild (Node* newChild) {child = newChild;}
};
		
class Inverter : public DecoratorNode {  // Inverts the result of the child. A child fails and it will return success to its parent, or a child succeeds and it will return failure to the parent.
			private:
				virtual bool run() override {return !getChild()->run();}
};

//status

struct PositionStatus {
	bool iAmAttacker;
	bool iHaveBallPossession;
	bool enemyHaveBallPossession;
	bool noOneHaveBallPossession;
	bool allyHaveBallPossession;
	bool behindEnemy;
	bool ballclose;
	int dball;
};

//conditional nodes

class CheckIfRobotIsAttacker : public Node {  // Each task will be a class (derived from Node of course).
	private:
		PositionStatus* status;
	public:
		CheckIfRobotIsAttacker (PositionStatus* status) : status(status) {}
		virtual bool run() override {
			if (status->iAmAttacker == true){
				std::cout << "Robot is a attacker||defender" << std::endl;  // will return true
			return true;
			} else {
				return false;
			}
		}
};

class CheckIfIHaveBallPossession : public Node {
	private:
		PositionStatus* status;
	public:
		CheckIfIHaveBallPossession (PositionStatus* status) : status(status) {}
		virtual bool run() override {
			if (status->iHaveBallPossession == true){
			std::cout << "Robot have the ball possession" << std::endl;  // will return true
			return true;
		}
			else {
			return false;
		}
		}
};

class CheckIfEnemyHaveBallPossession : public Node {
	private:
		PositionStatus* status;
	public:
		CheckIfEnemyHaveBallPossession (PositionStatus* status) : status(status) {}
		virtual bool run() override {
			if (status->enemyHaveBallPossession == true){
			std::cout << "Enemy have the ball possession" << std::endl;  // will return true
			return true;
		}
			else {
			return false;
		}
		}
};

class CheckIfNoOneHaveBallPossession : public Node {
	private:
		PositionStatus* status;
	public:
		CheckIfNoOneHaveBallPossession (PositionStatus* status) : status(status) {}
		virtual bool run() override {
			if (status->noOneHaveBallPossession == true){
			std::cout << "no one have the ball possession" << std::endl;  // will return true
			return true;
		}
			else {
			return false;
		}
		}
};

class CheckIfAllyHaveBallPossession : public Node {
	private:
		PositionStatus* status;
	public:
		CheckIfAllyHaveBallPossession (PositionStatus* status) : status(status) {}
		virtual bool run() override {
			if (status->allyHaveBallPossession == true){
			std::cout << "Ally have the ball possession" << std::endl;  // will return true
			return true;
		}
			else {
			return false;
		}
		}
};

class BehindEnemy : public Node {
	private:
		PositionStatus* status;
	public:
		BehindEnemy (PositionStatus* status) : status(status) {}
		virtual bool run() override {
			if (status->behindEnemy == true){
				std::cout << "Robot is behind enemy" << std::endl;  // will return true
									return true;
			} else {
				return false;
			}
		}
};

class BallClose : public Node {
	private:
		PositionStatus* status;
	public:
		BallClose (PositionStatus* status) : status(status) {}
		virtual bool run() override {
			if (status->ballclose == true){
				std::cout << "Ball is close" << std::endl;  // will return true
				return true;
			} else {
				std::cout << "Ball is not close" << std::endl;
				return false;
			}
		}
};

class DMax : public Node {
	private:
		PositionStatus* status;
	public:
		DMax (PositionStatus* status) : status(status) {}
		virtual bool run() override {
			if (status->dball > 10){
				std::cout << "Dball > X=10cm" << std::endl;  // will return true
				return true;
			} else {
				std::cout << "Dball <= X=10cm" << std::endl;
				return false;
			}
		}
};

// action nodes

class Action : public Node {
	private:
		std::string name;
		int probabilityOfSuccess;
	public:
		Action (const std::string newName, int prob) : name(newName), probabilityOfSuccess(prob) {}
	private:
		virtual bool run() override {
			if (std::rand() % 100 < probabilityOfSuccess) {
				std::cout << name << " succeeded." << std::endl;
				return true;
			}
			std::cout << name << " failed." << std::endl;
			return false;
		}
};

int main() {

	Selector *root = new Selector; 

	// In general there will be several nodes that are Sequence or Selector, so they should be suffixed by an integer to distinguish between them.
	Sequence *sequence1 = new Sequence, *sequence2 = new Sequence, *sequence3 = new Sequence, *sequence4 = new Sequence, *sequence5 = new Sequence, *sequence6 = new Sequence, *sequence7 = new Sequence;
	Sequence *sequence8 = new Sequence, *sequence9 = new Sequence, *sequence10 = new Sequence, *sequence11 = new Sequence, *sequence12 = new Sequence, *sequence13 = new Sequence, *sequence14 = new Sequence; 
	Selector *selector1 = new Selector, *selector2 = new Selector, *selector3 = new Selector, *selector4 = new Selector, *selector5 = new Selector;  
	Inverter *inverter1 = new Inverter, *inverter2 = new Inverter, *inverter3 = new Inverter, *inverter4 = new Inverter;

	// The robot is initially attacker, enemy have the ball and robot is behind enemy
    PositionStatus* positionStatus = new PositionStatus {true, false, true, false, false, true, false, 9};  

	//checks
    CheckIfRobotIsAttacker* checkAttacker = new CheckIfRobotIsAttacker (positionStatus);

	CheckIfIHaveBallPossession* iHaveBallPossession = new CheckIfIHaveBallPossession (positionStatus);
	CheckIfEnemyHaveBallPossession* enemyHaveBallPossession = new CheckIfEnemyHaveBallPossession (positionStatus);
	CheckIfNoOneHaveBallPossession* noOneHaveBallPossession = new CheckIfNoOneHaveBallPossession (positionStatus);
	CheckIfAllyHaveBallPossession* allyHaveBallPossession = new CheckIfAllyHaveBallPossession (positionStatus);
	BehindEnemy* behindEnemy = new BehindEnemy (positionStatus);
	BallClose* ballClose = new BallClose (positionStatus);
	DMax* dMax = new DMax (positionStatus);
	
	//actions
	Action* attack = new Action ("Attack action", 100);
	Action* backtoarea = new Action ("Back to the area", 100);
	Action* defend = new Action ("Defender", 100);
	Action* goclose = new Action ("Go close to defender", 100);
	Action* waitcenter = new Action ("Wait in the center of area", 100);
	Action* followarea = new Action ("Follow the ball inside the area", 100);
	Action* rotate = new Action ("Rotate to push the ball away", 100);
	Action* follow = new Action ("Follow the ball", 100);
	
	root->addChild (sequence1);
		sequence1->addChild (checkAttacker);
		sequence1->addChild (selector1);
			selector1->addChild (sequence2);
				sequence2->addChild (iHaveBallPossession);
				sequence2->addChild (attack);
			selector1->addChild (sequence3);
				sequence3->addChild (enemyHaveBallPossession);
				sequence3->addChild (selector2);
					selector2->addChild (sequence6);
						sequence6->addChild (behindEnemy);
						sequence6->addChild (backtoarea);
					selector2->addChild (sequence7);
						sequence7->addChild (inverter4);
							inverter4->setChild (behindEnemy);
						sequence7->addChild (defend);
			selector1->addChild (sequence4);
				sequence4->addChild (noOneHaveBallPossession);
				sequence4->addChild (attack);
			selector1->addChild (sequence5);
				sequence5->addChild (allyHaveBallPossession);
				sequence5->addChild (goclose);

	root->addChild (sequence8);
		sequence8->addChild (inverter3);
				 inverter3->setChild (checkAttacker);
		sequence8->addChild (selector3);
			selector3->addChild (sequence9);
				sequence9->addChild (ballClose);
				sequence9->addChild (selector4);
					selector4->addChild (sequence11);
						sequence11->addChild (enemyHaveBallPossession);
						sequence11->addChild (selector5);
							selector5->addChild (sequence13);
								sequence13->addChild (inverter1);
									inverter1->setChild (dMax);
								sequence13->addChild (rotate);
							selector5->addChild (sequence14);
								sequence14->addChild (dMax);
								sequence14->addChild (follow);
					selector4->addChild (sequence12);
						sequence12->addChild (allyHaveBallPossession);
						sequence12->addChild (followarea);
			selector3->addChild (sequence10);
				sequence10->addChild (inverter2);
					inverter2->setChild (ballClose);
				sequence10->addChild (waitcenter);

		root->run();
		std::cout << "--------------------" << std::endl;

	std::cout << std::endl << "Behaviour tree exited." << std::endl;
}
