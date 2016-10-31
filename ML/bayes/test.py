# coding: utf-8

from bayes import *

def test_summarize():
    dataset = [[1, 20, 0], [2, 21, 1], [3, 22, 0]]
    summary = summarize(dataset)
    print('Attribute summaries: {0}').format(summary)

def test_summarizeByClass():
    dataset = [[1, 20, 1], [2, 21, 0], [3, 22, 1], [4, 22, 0]]
    summary = summarizeByClass(dataset)
    print('Summary by class value: {0}').format(summary)

def test_calculateProbability():
    x = 71.5
    mean = 73
    stdev = 6.2
    probability = calculateProbability(x, mean, stdev)
    print('Probability of belonging to this class: {0}').format(probability)

def test_calculateClassProbabilities():
    summaries = {0: [(1, 0.5)], 1: [(20, 5.0)]}
    inputVector = [1.1, '?']
    probabilities = calculateClassProbabilities(summaries, inputVector)
    print('Probabilities for each class: {0}').format(probabilities)

def test_predict():
    summaries = {'A': [(1, 0.5)], 'B': [(20, 5.0)]}
    inputVector = [1.1, '?']
    result = predict(summaries, inputVector)
    print 'Prediction: {0}'.format(result)


if __name__ == '__main__':
    # test_summarize()
    # test_summarizeByClass()
    # test_calculateProbability()
    # test_calculateClassProbabilities()
    test_predict()