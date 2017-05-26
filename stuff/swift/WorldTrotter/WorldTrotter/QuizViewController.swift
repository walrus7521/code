//
//  QuizViewController.swift
//  WorldTrotter
//
//  Created by Bart Bartel on 10/29/16.
//  Copyright © 2016 Bart Bartel. All rights reserved.
//

import UIKit

class QuizViewController: UIViewController {
    
    @IBOutlet var currentQuestionLabel: UILabel!
    @IBOutlet var currentQuestionLabelCenterXConstraint: NSLayoutConstraint!
    
    @IBOutlet var nextQuestionLabel: UILabel!
    @IBOutlet var nextQuestionLabelCenterXConstraint: NSLayoutConstraint!
    
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
        nextQuestionLabel.text = question
        answerLabel.text = "???"
        animateLabelTransitions()
    }
    
    @IBAction func showAnswer(sender: AnyObject) {
        let answer: String = answers[currentQuestionIndex]
        answerLabel.text = answer
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        let question = questions[currentQuestionIndex]
        //view.backgroundColor = UIColor.yellow // bad bad, don't access views here
        currentQuestionLabel.text = question
        title = "Quiz"
               
        updateOffScreenLabel()
        
    }
    
    func animateLabelTransitions() {
        UIView.animate(withDuration: 1.0,
            delay: 0,
            options: [],
            animations: {
                self.currentQuestionLabel.alpha = 0
                self.nextQuestionLabel.alpha = 1
            },
            completion: { _ in
                swap(&self.currentQuestionLabel,
                     &self.nextQuestionLabel)
            })

    }
    
    func updateOffScreenLabel() {
        let screenWidth = view.frame.width
        nextQuestionLabelCenterXConstraint.constant = -screenWidth
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        // set the label's initial alpha
        nextQuestionLabel.alpha = 0
    }
    
    
}

