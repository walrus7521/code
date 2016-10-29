//
//  QuizViewController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/29/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class QuizViewController: UIViewController {
    
    @IBOutlet var questionLabel: UILabel!
    @IBOutlet var answerLabel: UILabel!
    
    let questions: [String] = ["From what is cognac made?",
                               "What is 7+7?",
                               "What is the capital of Vermont?"]
    
    let answers: [String] = ["Grapes",
                             "14",
                             "Montpelier"]
    
    var currentQuestionIndex: Int = 0
    
    @IBAction func showNextQuestion(sender: AnyObject) {
        currentQuestionIndex = currentQuestionIndex + 1
        if currentQuestionIndex == questions.count {
            currentQuestionIndex = 0
        }
        let question: String = questions[currentQuestionIndex]
        questionLabel.text = question
    }
    
    @IBAction func showAnswer(sender: AnyObject) {
        let answer: String = answers[currentQuestionIndex]
        answerLabel.text = answer
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        //view.backgroundColor = UIColor.yellow // bad bad, don't access views here
        //title = "QuizView"
        //if questionLabel != nil {
        //    questionLabel.text = "hello, world"
        //}
        
        //let storyboard = UIStoryboard(name: "Main", bundle: nil)
        //let vc = storyboard.instantiateViewController(withIdentifier: "QuizViewControllerId")
        //self.navigationController!.pushViewController(vc, animated: true)
        
        //questionLabel.text = questions[currentQuestionIndex]
        
        //view.backgroundColor = UIColor.yellow // bad bad, don't access views here
        title = "QuizView"
        
        
    }
    
    //func animateLabelTransitions() {
    //    let animationClosure = { () -> Void in
    //    }
    //}
    
}

