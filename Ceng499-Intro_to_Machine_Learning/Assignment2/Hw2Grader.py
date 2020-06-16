import sys
import traceback
import numpy as np

if len(sys.argv) != 2:
    print "Usage: python Hw2Grader.py <SubmissionDirectory>"
    sys.exit(1)

submission_directory = sys.argv[1]
EPSILON = 0.0001

import sys

sys.path.append(submission_directory + '/Source')
print """
########################################################################################################################
########################                                                                        ########################
########################                                                                        ########################
########################                             MyKMeans                                   ########################
########################                                                                        ########################
########################                                                                        ########################
########################################################################################################################
"""

part1_data = [np.array([[1., 2.], [1., 4.], [1., 0.],
                        [4., 2.], [4., 4.], [4., 0.]]),
              np.array([[1., 1.], [1.5, 2.], [3., 4.],
                        [5., 7.], [3.5, 5.], [4.5, 5.], [3.5, 4.5]]),
              ]

from MyKMeans import MyKMeans

# (seed, n_clusters, init_method, (tuple of accepted answers))
part1_initalizes = [[(0, 2, 'kmeans++', (np.array([[4., 4.], [1., 0.]]),)),
                     (0, 2, 'random', (np.array([[4., 0.], [1., 0.]]),)),
                     ],
                    [(0, 2, 'kmeans++', (np.array([[3.5, 5.], [1.5, 2.]]), np.array([[3.5, 5.], [1., 1.]]))),
                     (0, 2, 'random', (np.array([[3.5, 4.5], [3., 4.]]),)),
                     ],
                    ]

PART1_INITIALIZATION_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part1_data):
    for j, initialize_test in enumerate(part1_initalizes[i]):
        test_count += 1
        try:
            correct = False
            seed = initialize_test[0]
            n_clusters = initialize_test[1]
            init_method = initialize_test[2]
            accepted_answers = initialize_test[3]
            kmeans = MyKMeans(n_clusters=n_clusters, random_state=seed, init_method=init_method)
            answer = np.array(kmeans.initialize(test_data), dtype=float)
            for accepted_answer in accepted_answers:
                if (answer == accepted_answer).all():
                    correct = True
                    break

            if correct:
                PART1_INITIALIZATION_GRADE += 1
            else:
                print "Wrong answer on data", i, "initialize test", j, ":"
                print "Given answer:", answer
                print "Accepted answers:", accepted_answers
        except Exception as e:
            print "Exception on data", i, "initialize test", j, ":"
            print "Configuration:", initialize_test
            print "Exception:", e
            traceback.print_exc()

PART1_INITIALIZATION_GRADE = PART1_INITIALIZATION_GRADE / test_count * 10

# (seed, n_clusters, initial_centers, (tuple of accepted answers for cluster_centers))
part1_fit = [[(0, 2, np.array([[4., 4.], [1., 0.]]), (np.array([[3., 3.33333333], [2., 0.66666667]]),)), ],
             [(0, 2, np.array([[3.5, 4.5], [3., 4.]]), (np.array([[3.9, 5.1], [1.25, 1.5]]),)), ],

             ]
PART1_FIT_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part1_data):
    for j, fit_test in enumerate(part1_fit[i]):
        test_count += 1
        try:
            correct = False
            seed = fit_test[0]
            n_clusters = fit_test[1]
            cluster_centers = fit_test[2]
            accepted_answers = fit_test[3]
            kmeans = MyKMeans(n_clusters=n_clusters, random_state=seed, init_method='manual',
                              cluster_centers=cluster_centers)
            kmeans.initialize(test_data)
            kmeans.fit(test_data)
            answer = kmeans.cluster_centers
            for x in range(answer.shape[1]):
                answer = answer[answer[:, x].argsort(kind='mergesort')]

            for accepted_answer in accepted_answers:
                correct_answer = accepted_answer
                for x in range(correct_answer.shape[1]):
                    correct_answer = correct_answer[
                        correct_answer[:, x].argsort(kind='mergesort')]

                if np.linalg.norm(correct_answer - answer) < EPSILON:
                    correct = True
                    break
            if correct:
                PART1_FIT_GRADE += 1
            else:
                print "Wrong answer on data", i, "fit test", j, ":"
                print "Given answer:", answer
                print "Accepted answers:", accepted_answers
        except Exception as e:
            print "Exception on data", i, "fit test", j, ":"
            print "Configuration:", fit_test
            print "Exception:", e
            traceback.print_exc()

PART1_FIT_GRADE = PART1_FIT_GRADE / test_count * 8

# (n_clusters, cluster_centers, data_to_predict, labels)
part1_predict = [[(2, np.array([[4., 2.], [1., 2.]]), np.array([[0, 0], [4, 4]]), np.array([1, 0])),
                  (2, np.array([[3., 3.33333333], [2., 0.66666667]]), np.array([[0, 0], [4, 4]]), np.array([1, 0]))],
                 [(2, np.array([[3.9, 5.1], [1.25, 1.5]]), np.array([[0.2, 4.1], [6.2, 4.3], [2.3, 7.8]]),
                   np.array([1, 0, 0])),
                  (4, np.array([[0., 0.], [5., 5.], [10., 10.], [15., 15.]]),
                   np.array([[0.2, 0.2], [4.7, 4.7], [6.1, 6.1], [16.4, 16.4]]), np.array([0, 1, 1, 3])),
                  ]

                 ]
PART1_PREDICT_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part1_data):
    for j, predict_test in enumerate(part1_predict[i]):
        test_count += 1
        try:
            n_clusters = predict_test[0]
            cluster_centers = predict_test[1]
            data_to_predict = predict_test[2]
            accepted_answer = predict_test[3]
            kmeans = MyKMeans(n_clusters=n_clusters, random_state=0, init_method='manual',
                              cluster_centers=cluster_centers)
            kmeans.initialize(test_data)
            kmeans.fit(test_data)
            kmeans.cluster_centers = cluster_centers
            answer = kmeans.predict(data_to_predict)

            if np.linalg.norm(accepted_answer - answer) < EPSILON:
                PART1_PREDICT_GRADE += 1
            else:
                print "Wrong answer on data", i, "predict test", j, ":"
                print "Given answer:", answer
                print "Accepted answers:", accepted_answer
        except Exception as e:
            print "Exception on data", i, "predict test", j, ":"
            print "Configuration:", predict_test
            print "Exception:", e
            traceback.print_exc()

PART1_PREDICT_GRADE = PART1_PREDICT_GRADE / test_count * 4

# (n_clusters, method, seed, tuple of accepted answers for predictions)
part1_fit_predict = [[(2, 'random', 0, (np.array([1, 1, 1, 0, 0, 0]), np.array([0, 0, 0, 1, 1, 1]))),
                      (2, 'kmeans++', 0, (np.array([1, 0, 1, 0, 0, 1]), np.array([0, 1, 0, 1, 1, 0]))), ],
                     [(2, 'random', 0, (np.array([1, 1, 0, 0, 0, 0, 0]),)),
                      (2, 'kmeans++', 0, (np.array([1, 1, 0, 0, 0, 0, 0]),)), ]

                     ]
PART1_FIT_PREDICT_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part1_data):
    for j, fit_predict_test in enumerate(part1_fit_predict[i]):
        test_count += 1
        try:
            correct = False
            n_clusters = fit_predict_test[0]
            method = fit_predict_test[1]
            seed = fit_predict_test[2]
            accepted_answers = fit_predict_test[3]
            kmeans = MyKMeans(n_clusters=n_clusters, random_state=seed, init_method=method)
            kmeans.initialize(test_data)
            answer = kmeans.fit_predict(test_data)

            for accepted_answer in accepted_answers:
                if np.linalg.norm(accepted_answer - answer) < EPSILON:
                    correct = True

            if correct:
                PART1_FIT_PREDICT_GRADE += 1
            else:
                print "Wrong answer on data", i, "predict test", j, ":"
                print "Given answer:", answer
                print "Accepted answers:", accepted_answer
        except Exception as e:
            print "Exception on data", i, "fit_predict test", j, ":"
            print "Configuration:", fit_predict_test
            print "Exception:", e
            traceback.print_exc()

PART1_FIT_PREDICT_GRADE = PART1_FIT_PREDICT_GRADE / test_count * 3

print """
########################################################################################################################
########################                                                                        ########################
########################                                                                        ########################
########################                             MyKMedoids                                 ########################
########################                                                                        ########################
########################                                                                        ########################
########################################################################################################################
"""

from MyKMedoids import MyKMedoids

part2_data = [np.array([np.array([2., 6.]),
                        np.array([3., 4.]),
                        np.array([3., 8.]),
                        np.array([4., 7.]),
                        np.array([6., 2.]),
                        np.array([6., 4.]),
                        np.array([7., 3.]),
                        np.array([7., 4.]),
                        np.array([8., 5.]),
                        np.array([7., 6.])
                        ]),
              np.array([[1., 1.], [1.5, 2.], [3., 4.],
                        [5., 7.], [3.5, 5.], [4.5, 5.], [3.5, 4.5]]),
              np.array([[1., 2.], [1., 4.], [1., 0.],
                        [4., 2.], [4., 4.], [4., 0.]])

              ]

# (n_clusters, seed, tuple of accepted answers for (best_medoids, min_cost))
part2_pam = [(2, 0, ((np.array([np.array([2., 6.]), np.array([7., 4.])]), 28.0),)),
             (2, 0, ((np.array([np.array([3.5, 5.]), np.array([1.5, 2.])]), 10.0),)),
             (2, 0, ((np.array([np.array([4., 0.]), np.array([4., 2.])]), 35.0),
                     (np.array([np.array([4., 2.]), np.array([1., 2.])]), 25.0))),
             ]

PART2_PAM_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part2_data):
    pam_test = part2_pam[i]
    test_count += 1
    try:
        correct = False
        n_clusters = pam_test[0]
        seed = pam_test[1]
        accepted_answers = pam_test[2]
        for accepted_answer in accepted_answers:
            accepted_answer = accepted_answer[0][accepted_answer[0][:, 1].argsort()], accepted_answer[1]

            kmedoids = MyKMedoids(method='pam', n_clusters=n_clusters, max_iter=300, random_state=seed)
            answer = kmedoids.pam(test_data)
            answer = np.array(answer[0]), answer[1]
            answer = answer[0][answer[0][:, 1].argsort()], answer[1]
            if abs(accepted_answer[1] - answer[1]) < EPSILON and (accepted_answer[0] == answer[0]).all():
                correct = True
                break
        if correct:
            PART2_PAM_GRADE += 1
        else:
            print "Wrong answer on data", i, " pam_test:"
            print "Given answer:", answer
            print "Accepted answer:", accepted_answer
    except Exception as e:
        print "Exception on data", i, " pam_test:"
        print "Configuration:", pam_test
        print "Exception:", e
        traceback.print_exc()

PART2_PAM_GRADE = PART2_PAM_GRADE / test_count * 8

# (n_clusters, seed, sample_ratio, clara_trials, tuple of accepted answer for (best_medoids, min_cost))
part2_clara = [(2, 0, 0.5, 10, ((np.array([np.array([4., 7.]), np.array([7., 4.])]), 30.0),)),
               (3, 0, 0.5, 5, ((np.array([np.array([1.5, 2.]), np.array([1., 1.]), np.array([3.5, 4.5])]), 10.5),
                               (np.array([np.array([1.5, 2.]), np.array([3., 4.]), np.array([5., 7.])]), 6.25),)),
               (2, 0, 0.5, 20, ((np.array([np.array([1., 2.]), np.array([4., 2.])]), 16.0),
                                (np.array([np.array([1., 4.]), np.array([4., 2.])]), 25.0),)),
               ]

PART2_CLARA_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part2_data):
    clara_test = part2_clara[i]
    test_count += 1
    try:
        correct = False
        n_clusters = clara_test[0]
        seed = clara_test[1]
        sample_ratio = clara_test[2]
        clara_trials = clara_test[3]
        accepted_answers = clara_test[4]
        for accepted_answer in accepted_answers:
            accepted_answer = accepted_answer[0][accepted_answer[0][:, 1].argsort()], accepted_answer[1]

            kmedoids = MyKMedoids(method='clara', n_clusters=n_clusters, sample_ratio=sample_ratio,
                                  clara_trials=clara_trials, max_iter=300, random_state=seed)
            kmedoids.fit(test_data)
            best_medoids = np.array(kmedoids.best_medoids)
            min_cost = kmedoids.min_cost
            best_medoids = best_medoids[best_medoids[:, 1].argsort()]
            answer = best_medoids, min_cost

            if abs(accepted_answer[1] - answer[1]) < EPSILON and (accepted_answer[0] == answer[0]).all():
                correct = True
                break
        if correct:
            PART2_CLARA_GRADE += 1
        else:
            print "Wrong answer on data", i, " clara_test:"
            print "Given answer:", answer
            print "Accepted answer:", accepted_answer
    except Exception as e:
        print "Exception on data", i, " clara_test:"
        print "Configuration:", clara_test
        print "Exception:", e
        traceback.print_exc()

PART2_CLARA_GRADE = PART2_CLARA_GRADE / test_count * 6

# (medoids, accepted_answers)
part2_generate_clusters = [(np.array([[3., 3.], [5., 5.]]),
                            [np.array([np.array([2., 6.]), np.array([3., 4.]), np.array([6., 2.])]), np.array(
                                [np.array([3., 8.]), np.array([4., 7.]), np.array([6., 4.]), np.array([7., 3.]),
                                 np.array([7., 4.]), np.array([8., 5.]), np.array([7., 6.])])]),
                           (np.array([[2., 2.], [4., 4.]]), [np.array([np.array([1., 1.]), np.array([1.5, 2.])]),
                                                             np.array([np.array([3., 4.]), np.array([5., 7.]),
                                                                       np.array([3.5, 5.]), np.array([4.5, 5.]),
                                                                       np.array([3.5, 4.5])])]),
                           (np.array([[1., 2.], [4., 2.]]), [np.array([np.array([1., 4.]), np.array([1., 0.])]),
                                                             np.array([np.array([4., 4.]), np.array([4., 0.])])])
                           ]
PART2_CLUSTER_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part2_data):
    cluster_test = part2_generate_clusters[i]
    test_count += 1
    try:
        correct = False
        n_clusters = len(cluster_test[0])
        seed = 0
        accepted_answer = cluster_test[1]
        accepted_answer = [x[x[:, 1].argsort()] for x in accepted_answer]

        kmedoids = MyKMedoids(method='pam', n_clusters=n_clusters, max_iter=300, random_state=seed)
        answer = kmedoids.generate_clusters(cluster_test[0], test_data)
        answer = [np.array(x)[np.array(x)[:, 1].argsort()] for x in answer]
        if all([np.allclose(x, y) for x, y in zip(answer, accepted_answer)]):
            PART2_CLUSTER_GRADE += 1
        else:
            print "Wrong answer on data", i, " cluster_test:"
            print "Given answer:", answer
            print "Accepted answer:", accepted_answer
    except Exception as e:
        print "Exception on data", i, " cluster_test:"
        print "Configuration:", cluster_test
        print "Exception:", e
        traceback.print_exc()

PART2_CLUSTER_GRADE = PART2_CLUSTER_GRADE / test_count * 4

# (best_medoids, data_to_predict, accepted_answer)
part2_predict = [(np.array([[0.], [5.], [10.]]), np.array([[2.], [4.], [9.]]), np.array([0, 1, 2])),
                 (np.array([[0., 0.], [5., 5.], [10., 10.]]), np.array([[2., 2.], [4., 4.], [9., 9.]]),
                  np.array([0, 1, 2])),
                 (np.array([[1., 2.], [1., 4.], [1., 0.], [4., 2.], [4., 4.], [4., 0.]]), np.array(
                     [[3.52631211, 2.73700839], [6.1956103, 4.04136827], [8.13862915, 8.20435963],
                      [2.35755202, 7.6443907], [3.08649252, 6.34264951], [6.44789606, 2.51355147],
                      [6.84186628, 8.46346045], [0.18573246, 4.2932754], [9.07918455, 0.6869116],
                      [1.69796189, 2.30647961], [0.91907182, 3.08052133], [0.46477331, 2.76759342],
                      [5.97959213, 0.20932529], [1.71434965, 0.7970043], [3.63702014, 5.40371041],
                      [8.86814881, 3.56607067], [4.26212678, 6.30692154], [3.90855351, 6.94301648],
                      [6.26192201, 0.47864105], [0.53241515, 9.47972025]]),
                  np.array([3, 4, 4, 1, 4, 3, 4, 1, 5, 0, 1, 0, 5, 2, 4, 4, 4, 4, 5, 1]))
                 ]
PART2_PREDICT_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part2_data):
    predict_test = part2_predict[i]
    test_count += 1
    try:
        correct = False
        n_clusters = len(predict_test[0])
        seed = 0
        data_to_predict = predict_test[1]
        accepted_answer = predict_test[2]

        kmedoids = MyKMedoids(method='pam', n_clusters=n_clusters, max_iter=300, random_state=seed)
        kmedoids.best_medoids = predict_test[0]

        answer = kmedoids.predict(data_to_predict)
        if all([np.allclose(x, y) for x, y in zip(answer, accepted_answer)]):
            PART2_PREDICT_GRADE += 1
        else:
            print "Wrong answer on data", i, " predict_test:"
            print "Given answer:", answer
            print "Accepted answer:", accepted_answer
    except Exception as e:
        print "Exception on data", i, " predict_test:"
        print "Configuration:", predict_test
        print "Exception:", e
        traceback.print_exc()

PART2_PREDICT_GRADE = PART2_PREDICT_GRADE / test_count * 4
# (n_clusters, accepted answers)
part2_fit_predict = [(5, (np.array([2, 3, 2, 2, 1, 4, 1, 4, 0, 0]), np.array([0, 4, 0, 0, 2, 2, 2, 2, 1, 3]))),
                     (2, (np.array([1, 1, 0, 0, 0, 0, 0]),)),
                     (3, (np.array([2, 2, 0, 1, 1, 0]), np.array([1, 2, 1, 0, 2, 0])))

                     ]

PART2_FIT_PREDICT_GRADE = 0
test_count = 0.
for i, test_data in enumerate(part2_data):
    fit_predict_test = part2_fit_predict[i]
    test_count += 1
    try:
        correct = False
        n_clusters = fit_predict_test[0]
        seed = 0
        accepted_answers = fit_predict_test[1]
        for accepted_answer in accepted_answers:

            kmedoids = MyKMedoids(method='pam', n_clusters=n_clusters, max_iter=300, random_state=seed)

            answer = kmedoids.fit_predict(test_data)
            if all([np.allclose(x, y) for x, y in zip(answer, accepted_answer)]):
                correct = True
                break
        if correct:
            PART2_FIT_PREDICT_GRADE += 1
        else:
            print "Wrong answer on data", i, " fit_predict_test:"
            print "Given answer:", answer
            print "Accepted answer:", accepted_answer
    except Exception as e:
        print "Exception on data", i, " fit_predict_test:"
        print "Configuration:", fit_predict_test
        print "Exception:", e
        traceback.print_exc()

PART2_FIT_PREDICT_GRADE = PART2_FIT_PREDICT_GRADE / test_count * 3

print """
########################################################################################################################
########################                                                                        ########################
########################                                                                        ########################
########################                        MyKNeighborsClassifier                          ########################
########################                                                                        ########################
########################                                                                        ########################
########################################################################################################################
"""

# [(n_neighbors, X, y)]
part3_data = [(3, np.array([[0.], [1.], [5.], [100.]]), np.array([0, 0, 1, 1]), 'l2'),
              (5, np.array([[5.1, 3.5, 1.4, 0.2],
                            [4.9, 3., 1.4, 0.2],
                            [4.7, 3.2, 1.3, 0.2],
                            [4.6, 3.1, 1.5, 0.2],
                            [5., 3.6, 1.4, 0.2],
                            [5.4, 3.9, 1.7, 0.4],
                            [4.6, 3.4, 1.4, 0.3],
                            [5., 3.4, 1.5, 0.2],
                            [4.4, 2.9, 1.4, 0.2],
                            [4.9, 3.1, 1.5, 0.1],
                            [5.4, 3.7, 1.5, 0.2],
                            [4.8, 3.4, 1.6, 0.2],
                            [4.8, 3., 1.4, 0.1],
                            [4.3, 3., 1.1, 0.1],
                            [5.8, 4., 1.2, 0.2],
                            [5.7, 4.4, 1.5, 0.4],
                            [5.4, 3.9, 1.3, 0.4],
                            [5.1, 3.5, 1.4, 0.3],
                            [5.7, 3.8, 1.7, 0.3],
                            [5.1, 3.8, 1.5, 0.3],
                            [5.4, 3.4, 1.7, 0.2],
                            [5.1, 3.7, 1.5, 0.4],
                            [4.6, 3.6, 1., 0.2],
                            [5.1, 3.3, 1.7, 0.5],
                            [4.8, 3.4, 1.9, 0.2],
                            [5., 3., 1.6, 0.2],
                            [5., 3.4, 1.6, 0.4],
                            [5.2, 3.5, 1.5, 0.2],
                            [5.2, 3.4, 1.4, 0.2],
                            [4.7, 3.2, 1.6, 0.2],
                            [4.8, 3.1, 1.6, 0.2],
                            [5.4, 3.4, 1.5, 0.4],
                            [5.2, 4.1, 1.5, 0.1],
                            [5.5, 4.2, 1.4, 0.2],
                            [4.9, 3.1, 1.5, 0.2],
                            [5., 3.2, 1.2, 0.2],
                            [5.5, 3.5, 1.3, 0.2],
                            [4.9, 3.6, 1.4, 0.1],
                            [4.4, 3., 1.3, 0.2],
                            [5.1, 3.4, 1.5, 0.2],
                            [5., 3.5, 1.3, 0.3],
                            [4.5, 2.3, 1.3, 0.3],
                            [4.4, 3.2, 1.3, 0.2],
                            [5., 3.5, 1.6, 0.6],
                            [5.1, 3.8, 1.9, 0.4],
                            [4.8, 3., 1.4, 0.3],
                            [5.1, 3.8, 1.6, 0.2],
                            [4.6, 3.2, 1.4, 0.2],
                            [5.3, 3.7, 1.5, 0.2],
                            [5., 3.3, 1.4, 0.2],
                            [7., 3.2, 4.7, 1.4],
                            [6.4, 3.2, 4.5, 1.5],
                            [6.9, 3.1, 4.9, 1.5],
                            [5.5, 2.3, 4., 1.3],
                            [6.5, 2.8, 4.6, 1.5],
                            [5.7, 2.8, 4.5, 1.3],
                            [6.3, 3.3, 4.7, 1.6],
                            [4.9, 2.4, 3.3, 1.],
                            [6.6, 2.9, 4.6, 1.3],
                            [5.2, 2.7, 3.9, 1.4],
                            [5., 2., 3.5, 1.],
                            [5.9, 3., 4.2, 1.5],
                            [6., 2.2, 4., 1.],
                            [6.1, 2.9, 4.7, 1.4],
                            [5.6, 2.9, 3.6, 1.3],
                            [6.7, 3.1, 4.4, 1.4],
                            [5.6, 3., 4.5, 1.5],
                            [5.8, 2.7, 4.1, 1.],
                            [6.2, 2.2, 4.5, 1.5],
                            [5.6, 2.5, 3.9, 1.1],
                            [5.9, 3.2, 4.8, 1.8],
                            [6.1, 2.8, 4., 1.3],
                            [6.3, 2.5, 4.9, 1.5],
                            [6.1, 2.8, 4.7, 1.2],
                            [6.4, 2.9, 4.3, 1.3],
                            [6.6, 3., 4.4, 1.4],
                            [6.8, 2.8, 4.8, 1.4],
                            [6.7, 3., 5., 1.7],
                            [6., 2.9, 4.5, 1.5],
                            [5.7, 2.6, 3.5, 1.],
                            [5.5, 2.4, 3.8, 1.1],
                            [5.5, 2.4, 3.7, 1.],
                            [5.8, 2.7, 3.9, 1.2],
                            [6., 2.7, 5.1, 1.6],
                            [5.4, 3., 4.5, 1.5],
                            [6., 3.4, 4.5, 1.6],
                            [6.7, 3.1, 4.7, 1.5],
                            [6.3, 2.3, 4.4, 1.3],
                            [5.6, 3., 4.1, 1.3],
                            [5.5, 2.5, 4., 1.3],
                            [5.5, 2.6, 4.4, 1.2],
                            [6.1, 3., 4.6, 1.4],
                            [5.8, 2.6, 4., 1.2],
                            [5., 2.3, 3.3, 1.],
                            [5.6, 2.7, 4.2, 1.3],
                            [5.7, 3., 4.2, 1.2],
                            [5.7, 2.9, 4.2, 1.3],
                            [6.2, 2.9, 4.3, 1.3],
                            [5.1, 2.5, 3., 1.1],
                            [5.7, 2.8, 4.1, 1.3],
                            [6.3, 3.3, 6., 2.5],
                            [5.8, 2.7, 5.1, 1.9],
                            [7.1, 3., 5.9, 2.1],
                            [6.3, 2.9, 5.6, 1.8],
                            [6.5, 3., 5.8, 2.2],
                            [7.6, 3., 6.6, 2.1],
                            [4.9, 2.5, 4.5, 1.7],
                            [7.3, 2.9, 6.3, 1.8],
                            [6.7, 2.5, 5.8, 1.8],
                            [7.2, 3.6, 6.1, 2.5],
                            [6.5, 3.2, 5.1, 2.],
                            [6.4, 2.7, 5.3, 1.9],
                            [6.8, 3., 5.5, 2.1],
                            [5.7, 2.5, 5., 2.],
                            [5.8, 2.8, 5.1, 2.4],
                            [6.4, 3.2, 5.3, 2.3],
                            [6.5, 3., 5.5, 1.8],
                            [7.7, 3.8, 6.7, 2.2],
                            [7.7, 2.6, 6.9, 2.3],
                            [6., 2.2, 5., 1.5],
                            [6.9, 3.2, 5.7, 2.3],
                            [5.6, 2.8, 4.9, 2.],
                            [7.7, 2.8, 6.7, 2.],
                            [6.3, 2.7, 4.9, 1.8],
                            [6.7, 3.3, 5.7, 2.1],
                            [7.2, 3.2, 6., 1.8],
                            [6.2, 2.8, 4.8, 1.8],
                            [6.1, 3., 4.9, 1.8],
                            [6.4, 2.8, 5.6, 2.1],
                            [7.2, 3., 5.8, 1.6],
                            [7.4, 2.8, 6.1, 1.9],
                            [7.9, 3.8, 6.4, 2.],
                            [6.4, 2.8, 5.6, 2.2],
                            [6.3, 2.8, 5.1, 1.5],
                            [6.1, 2.6, 5.6, 1.4],
                            [7.7, 3., 6.1, 2.3],
                            [6.3, 3.4, 5.6, 2.4],
                            [6.4, 3.1, 5.5, 1.8],
                            [6., 3., 4.8, 1.8],
                            [6.9, 3.1, 5.4, 2.1],
                            [6.7, 3.1, 5.6, 2.4],
                            [6.9, 3.1, 5.1, 2.3],
                            [5.8, 2.7, 5.1, 1.9],
                            [6.8, 3.2, 5.9, 2.3],
                            [6.7, 3.3, 5.7, 2.5],
                            [6.7, 3., 5.2, 2.3],
                            [6.3, 2.5, 5., 1.9],
                            [6.5, 3., 5.2, 2.],
                            [6.2, 3.4, 5.4, 2.3],
                            [5.9, 3., 5.1, 1.8]]),
               np.array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                         2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                         2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]), 'l2'),
              ]

# [ (data_to_predict, labels)]
part3_classical_predict = [[(np.array([[0.9], [1.1], [4.9], [20.]]), np.array([0, 0, 0, 0])), ],
                           [(np.array([[5.1, 3.5, 1.4, 0.2],
                                       [4.9, 3., 1.4, 0.2],
                                       [4.7, 3.2, 1.3, 0.2],
                                       [4.6, 3.1, 1.5, 0.2],
                                       [5., 3.6, 1.4, 0.2],
                                       [5.4, 3.9, 1.7, 0.4],
                                       [4.6, 3.4, 1.4, 0.3],
                                       [5., 3.4, 1.5, 0.2],
                                       [4.4, 2.9, 1.4, 0.2],
                                       [4.9, 3.1, 1.5, 0.1],
                                       [5.4, 3.7, 1.5, 0.2],
                                       [4.8, 3.4, 1.6, 0.2],
                                       [4.8, 3., 1.4, 0.1],
                                       [4.3, 3., 1.1, 0.1],
                                       [5.8, 4., 1.2, 0.2],
                                       [5.7, 4.4, 1.5, 0.4],
                                       [5.4, 3.9, 1.3, 0.4],
                                       [5.1, 3.5, 1.4, 0.3],
                                       [5.7, 3.8, 1.7, 0.3],
                                       [5.1, 3.8, 1.5, 0.3],
                                       [5.4, 3.4, 1.7, 0.2],
                                       [5.1, 3.7, 1.5, 0.4],
                                       [4.6, 3.6, 1., 0.2],
                                       [5.1, 3.3, 1.7, 0.5],
                                       [4.8, 3.4, 1.9, 0.2],
                                       [5., 3., 1.6, 0.2],
                                       [5., 3.4, 1.6, 0.4],
                                       [5.2, 3.5, 1.5, 0.2],
                                       [5.2, 3.4, 1.4, 0.2],
                                       [4.7, 3.2, 1.6, 0.2],
                                       [4.8, 3.1, 1.6, 0.2],
                                       [5.4, 3.4, 1.5, 0.4],
                                       [5.2, 4.1, 1.5, 0.1],
                                       [5.5, 4.2, 1.4, 0.2],
                                       [4.9, 3.1, 1.5, 0.2],
                                       [5., 3.2, 1.2, 0.2],
                                       [5.5, 3.5, 1.3, 0.2],
                                       [4.9, 3.6, 1.4, 0.1],
                                       [4.4, 3., 1.3, 0.2],
                                       [5.1, 3.4, 1.5, 0.2],
                                       [5., 3.5, 1.3, 0.3],
                                       [4.5, 2.3, 1.3, 0.3],
                                       [4.4, 3.2, 1.3, 0.2],
                                       [5., 3.5, 1.6, 0.6],
                                       [5.1, 3.8, 1.9, 0.4],
                                       [4.8, 3., 1.4, 0.3],
                                       [5.1, 3.8, 1.6, 0.2],
                                       [4.6, 3.2, 1.4, 0.2],
                                       [5.3, 3.7, 1.5, 0.2],
                                       [5., 3.3, 1.4, 0.2],
                                       [7., 3.2, 4.7, 1.4],
                                       [6.4, 3.2, 4.5, 1.5],
                                       [6.9, 3.1, 4.9, 1.5],
                                       [5.5, 2.3, 4., 1.3],
                                       [6.5, 2.8, 4.6, 1.5],
                                       [5.7, 2.8, 4.5, 1.3],
                                       [6.3, 3.3, 4.7, 1.6],
                                       [4.9, 2.4, 3.3, 1.],
                                       [6.6, 2.9, 4.6, 1.3],
                                       [5.2, 2.7, 3.9, 1.4],
                                       [5., 2., 3.5, 1.],
                                       [5.9, 3., 4.2, 1.5],
                                       [6., 2.2, 4., 1.],
                                       [6.1, 2.9, 4.7, 1.4],
                                       [5.6, 2.9, 3.6, 1.3],
                                       [6.7, 3.1, 4.4, 1.4],
                                       [5.6, 3., 4.5, 1.5],
                                       [5.8, 2.7, 4.1, 1.],
                                       [6.2, 2.2, 4.5, 1.5],
                                       [5.6, 2.5, 3.9, 1.1],
                                       [5.9, 3.2, 4.8, 1.8],
                                       [6.1, 2.8, 4., 1.3],
                                       [6.3, 2.5, 4.9, 1.5],
                                       [6.1, 2.8, 4.7, 1.2],
                                       [6.4, 2.9, 4.3, 1.3],
                                       [6.6, 3., 4.4, 1.4],
                                       [6.8, 2.8, 4.8, 1.4],
                                       [6.7, 3., 5., 1.7],
                                       [6., 2.9, 4.5, 1.5],
                                       [5.7, 2.6, 3.5, 1.],
                                       [5.5, 2.4, 3.8, 1.1],
                                       [5.5, 2.4, 3.7, 1.],
                                       [5.8, 2.7, 3.9, 1.2],
                                       [6., 2.7, 5.1, 1.6],
                                       [5.4, 3., 4.5, 1.5],
                                       [6., 3.4, 4.5, 1.6],
                                       [6.7, 3.1, 4.7, 1.5],
                                       [6.3, 2.3, 4.4, 1.3],
                                       [5.6, 3., 4.1, 1.3],
                                       [5.5, 2.5, 4., 1.3],
                                       [5.5, 2.6, 4.4, 1.2],
                                       [6.1, 3., 4.6, 1.4],
                                       [5.8, 2.6, 4., 1.2],
                                       [5., 2.3, 3.3, 1.],
                                       [5.6, 2.7, 4.2, 1.3],
                                       [5.7, 3., 4.2, 1.2],
                                       [5.7, 2.9, 4.2, 1.3],
                                       [6.2, 2.9, 4.3, 1.3],
                                       [5.1, 2.5, 3., 1.1],
                                       [5.7, 2.8, 4.1, 1.3],
                                       [6.3, 3.3, 6., 2.5],
                                       [5.8, 2.7, 5.1, 1.9],
                                       [7.1, 3., 5.9, 2.1],
                                       [6.3, 2.9, 5.6, 1.8],
                                       [6.5, 3., 5.8, 2.2],
                                       [7.6, 3., 6.6, 2.1],
                                       [4.9, 2.5, 4.5, 1.7],
                                       [7.3, 2.9, 6.3, 1.8],
                                       [6.7, 2.5, 5.8, 1.8],
                                       [7.2, 3.6, 6.1, 2.5],
                                       [6.5, 3.2, 5.1, 2.],
                                       [6.4, 2.7, 5.3, 1.9],
                                       [6.8, 3., 5.5, 2.1],
                                       [5.7, 2.5, 5., 2.],
                                       [5.8, 2.8, 5.1, 2.4],
                                       [6.4, 3.2, 5.3, 2.3],
                                       [6.5, 3., 5.5, 1.8],
                                       [7.7, 3.8, 6.7, 2.2],
                                       [7.7, 2.6, 6.9, 2.3],
                                       [6., 2.2, 5., 1.5],
                                       [6.9, 3.2, 5.7, 2.3],
                                       [5.6, 2.8, 4.9, 2.],
                                       [7.7, 2.8, 6.7, 2.],
                                       [6.3, 2.7, 4.9, 1.8],
                                       [6.7, 3.3, 5.7, 2.1],
                                       [7.2, 3.2, 6., 1.8],
                                       [6.2, 2.8, 4.8, 1.8],
                                       [6.1, 3., 4.9, 1.8],
                                       [6.4, 2.8, 5.6, 2.1],
                                       [7.2, 3., 5.8, 1.6],
                                       [7.4, 2.8, 6.1, 1.9],
                                       [7.9, 3.8, 6.4, 2.],
                                       [6.4, 2.8, 5.6, 2.2],
                                       [6.3, 2.8, 5.1, 1.5],
                                       [6.1, 2.6, 5.6, 1.4],
                                       [7.7, 3., 6.1, 2.3],
                                       [6.3, 3.4, 5.6, 2.4],
                                       [6.4, 3.1, 5.5, 1.8],
                                       [6., 3., 4.8, 1.8],
                                       [6.9, 3.1, 5.4, 2.1],
                                       [6.7, 3.1, 5.6, 2.4],
                                       [6.9, 3.1, 5.1, 2.3],
                                       [5.8, 2.7, 5.1, 1.9],
                                       [6.8, 3.2, 5.9, 2.3],
                                       [6.7, 3.3, 5.7, 2.5],
                                       [6.7, 3., 5.2, 2.3],
                                       [6.3, 2.5, 5., 1.9],
                                       [6.5, 3., 5.2, 2.],
                                       [6.2, 3.4, 5.4, 2.3],
                                       [5.9, 3., 5.1, 1.8]]),
                             np.array(
                                 [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1,
                                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                  2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                  2, 2, 2, 2, 2]))]]

part3_weighted_predict = [[(np.array([[0.9], [1.1], [4.9], [20.]]), np.array([0, 0, 1, 0])), ],
                          [(np.array([[5.1, 3.5, 1.4, 0.2],
                                      [4.9, 3., 1.4, 0.2],
                                      [4.7, 3.2, 1.3, 0.2],
                                      [4.6, 3.1, 1.5, 0.2],
                                      [5., 3.6, 1.4, 0.2],
                                      [5.4, 3.9, 1.7, 0.4],
                                      [4.6, 3.4, 1.4, 0.3],
                                      [5., 3.4, 1.5, 0.2],
                                      [4.4, 2.9, 1.4, 0.2],
                                      [4.9, 3.1, 1.5, 0.1],
                                      [5.4, 3.7, 1.5, 0.2],
                                      [4.8, 3.4, 1.6, 0.2],
                                      [4.8, 3., 1.4, 0.1],
                                      [4.3, 3., 1.1, 0.1],
                                      [5.8, 4., 1.2, 0.2],
                                      [5.7, 4.4, 1.5, 0.4],
                                      [5.4, 3.9, 1.3, 0.4],
                                      [5.1, 3.5, 1.4, 0.3],
                                      [5.7, 3.8, 1.7, 0.3],
                                      [5.1, 3.8, 1.5, 0.3],
                                      [5.4, 3.4, 1.7, 0.2],
                                      [5.1, 3.7, 1.5, 0.4],
                                      [4.6, 3.6, 1., 0.2],
                                      [5.1, 3.3, 1.7, 0.5],
                                      [4.8, 3.4, 1.9, 0.2],
                                      [5., 3., 1.6, 0.2],
                                      [5., 3.4, 1.6, 0.4],
                                      [5.2, 3.5, 1.5, 0.2],
                                      [5.2, 3.4, 1.4, 0.2],
                                      [4.7, 3.2, 1.6, 0.2],
                                      [4.8, 3.1, 1.6, 0.2],
                                      [5.4, 3.4, 1.5, 0.4],
                                      [5.2, 4.1, 1.5, 0.1],
                                      [5.5, 4.2, 1.4, 0.2],
                                      [4.9, 3.1, 1.5, 0.2],
                                      [5., 3.2, 1.2, 0.2],
                                      [5.5, 3.5, 1.3, 0.2],
                                      [4.9, 3.6, 1.4, 0.1],
                                      [4.4, 3., 1.3, 0.2],
                                      [5.1, 3.4, 1.5, 0.2],
                                      [5., 3.5, 1.3, 0.3],
                                      [4.5, 2.3, 1.3, 0.3],
                                      [4.4, 3.2, 1.3, 0.2],
                                      [5., 3.5, 1.6, 0.6],
                                      [5.1, 3.8, 1.9, 0.4],
                                      [4.8, 3., 1.4, 0.3],
                                      [5.1, 3.8, 1.6, 0.2],
                                      [4.6, 3.2, 1.4, 0.2],
                                      [5.3, 3.7, 1.5, 0.2],
                                      [5., 3.3, 1.4, 0.2],
                                      [7., 3.2, 4.7, 1.4],
                                      [6.4, 3.2, 4.5, 1.5],
                                      [6.9, 3.1, 4.9, 1.5],
                                      [5.5, 2.3, 4., 1.3],
                                      [6.5, 2.8, 4.6, 1.5],
                                      [5.7, 2.8, 4.5, 1.3],
                                      [6.3, 3.3, 4.7, 1.6],
                                      [4.9, 2.4, 3.3, 1.],
                                      [6.6, 2.9, 4.6, 1.3],
                                      [5.2, 2.7, 3.9, 1.4],
                                      [5., 2., 3.5, 1.],
                                      [5.9, 3., 4.2, 1.5],
                                      [6., 2.2, 4., 1.],
                                      [6.1, 2.9, 4.7, 1.4],
                                      [5.6, 2.9, 3.6, 1.3],
                                      [6.7, 3.1, 4.4, 1.4],
                                      [5.6, 3., 4.5, 1.5],
                                      [5.8, 2.7, 4.1, 1.],
                                      [6.2, 2.2, 4.5, 1.5],
                                      [5.6, 2.5, 3.9, 1.1],
                                      [5.9, 3.2, 4.8, 1.8],
                                      [6.1, 2.8, 4., 1.3],
                                      [6.3, 2.5, 4.9, 1.5],
                                      [6.1, 2.8, 4.7, 1.2],
                                      [6.4, 2.9, 4.3, 1.3],
                                      [6.6, 3., 4.4, 1.4],
                                      [6.8, 2.8, 4.8, 1.4],
                                      [6.7, 3., 5., 1.7],
                                      [6., 2.9, 4.5, 1.5],
                                      [5.7, 2.6, 3.5, 1.],
                                      [5.5, 2.4, 3.8, 1.1],
                                      [5.5, 2.4, 3.7, 1.],
                                      [5.8, 2.7, 3.9, 1.2],
                                      [6., 2.7, 5.1, 1.6],
                                      [5.4, 3., 4.5, 1.5],
                                      [6., 3.4, 4.5, 1.6],
                                      [6.7, 3.1, 4.7, 1.5],
                                      [6.3, 2.3, 4.4, 1.3],
                                      [5.6, 3., 4.1, 1.3],
                                      [5.5, 2.5, 4., 1.3],
                                      [5.5, 2.6, 4.4, 1.2],
                                      [6.1, 3., 4.6, 1.4],
                                      [5.8, 2.6, 4., 1.2],
                                      [5., 2.3, 3.3, 1.],
                                      [5.6, 2.7, 4.2, 1.3],
                                      [5.7, 3., 4.2, 1.2],
                                      [5.7, 2.9, 4.2, 1.3],
                                      [6.2, 2.9, 4.3, 1.3],
                                      [5.1, 2.5, 3., 1.1],
                                      [5.7, 2.8, 4.1, 1.3],
                                      [6.3, 3.3, 6., 2.5],
                                      [5.8, 2.7, 5.1, 1.9],
                                      [7.1, 3., 5.9, 2.1],
                                      [6.3, 2.9, 5.6, 1.8],
                                      [6.5, 3., 5.8, 2.2],
                                      [7.6, 3., 6.6, 2.1],
                                      [4.9, 2.5, 4.5, 1.7],
                                      [7.3, 2.9, 6.3, 1.8],
                                      [6.7, 2.5, 5.8, 1.8],
                                      [7.2, 3.6, 6.1, 2.5],
                                      [6.5, 3.2, 5.1, 2.],
                                      [6.4, 2.7, 5.3, 1.9],
                                      [6.8, 3., 5.5, 2.1],
                                      [5.7, 2.5, 5., 2.],
                                      [5.8, 2.8, 5.1, 2.4],
                                      [6.4, 3.2, 5.3, 2.3],
                                      [6.5, 3., 5.5, 1.8],
                                      [7.7, 3.8, 6.7, 2.2],
                                      [7.7, 2.6, 6.9, 2.3],
                                      [6., 2.2, 5., 1.5],
                                      [6.9, 3.2, 5.7, 2.3],
                                      [5.6, 2.8, 4.9, 2.],
                                      [7.7, 2.8, 6.7, 2.],
                                      [6.3, 2.7, 4.9, 1.8],
                                      [6.7, 3.3, 5.7, 2.1],
                                      [7.2, 3.2, 6., 1.8],
                                      [6.2, 2.8, 4.8, 1.8],
                                      [6.1, 3., 4.9, 1.8],
                                      [6.4, 2.8, 5.6, 2.1],
                                      [7.2, 3., 5.8, 1.6],
                                      [7.4, 2.8, 6.1, 1.9],
                                      [7.9, 3.8, 6.4, 2.],
                                      [6.4, 2.8, 5.6, 2.2],
                                      [6.3, 2.8, 5.1, 1.5],
                                      [6.1, 2.6, 5.6, 1.4],
                                      [7.7, 3., 6.1, 2.3],
                                      [6.3, 3.4, 5.6, 2.4],
                                      [6.4, 3.1, 5.5, 1.8],
                                      [6., 3., 4.8, 1.8],
                                      [6.9, 3.1, 5.4, 2.1],
                                      [6.7, 3.1, 5.6, 2.4],
                                      [6.9, 3.1, 5.1, 2.3],
                                      [5.8, 2.7, 5.1, 1.9],
                                      [6.8, 3.2, 5.9, 2.3],
                                      [6.7, 3.3, 5.7, 2.5],
                                      [6.7, 3., 5.2, 2.3],
                                      [6.3, 2.5, 5., 1.9],
                                      [6.5, 3., 5.2, 2.],
                                      [6.2, 3.4, 5.4, 2.3],
                                      [5.9, 3., 5.1, 1.8]]),
                            np.array(
                                [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                 2, 2, 2, 2, 2]))],

                          ]
part3_validity_predict = [[(np.array([[0.9], [1.1], [4.9], [20.]]), np.array([0, 0, 0, 0])), ],
                          [(np.array([[5.1, 3.5, 1.4, 0.2],
                                      [4.9, 3., 1.4, 0.2],
                                      [4.7, 3.2, 1.3, 0.2],
                                      [4.6, 3.1, 1.5, 0.2],
                                      [5., 3.6, 1.4, 0.2],
                                      [5.4, 3.9, 1.7, 0.4],
                                      [4.6, 3.4, 1.4, 0.3],
                                      [5., 3.4, 1.5, 0.2],
                                      [4.4, 2.9, 1.4, 0.2],
                                      [4.9, 3.1, 1.5, 0.1],
                                      [5.4, 3.7, 1.5, 0.2],
                                      [4.8, 3.4, 1.6, 0.2],
                                      [4.8, 3., 1.4, 0.1],
                                      [4.3, 3., 1.1, 0.1],
                                      [5.8, 4., 1.2, 0.2],
                                      [5.7, 4.4, 1.5, 0.4],
                                      [5.4, 3.9, 1.3, 0.4],
                                      [5.1, 3.5, 1.4, 0.3],
                                      [5.7, 3.8, 1.7, 0.3],
                                      [5.1, 3.8, 1.5, 0.3],
                                      [5.4, 3.4, 1.7, 0.2],
                                      [5.1, 3.7, 1.5, 0.4],
                                      [4.6, 3.6, 1., 0.2],
                                      [5.1, 3.3, 1.7, 0.5],
                                      [4.8, 3.4, 1.9, 0.2],
                                      [5., 3., 1.6, 0.2],
                                      [5., 3.4, 1.6, 0.4],
                                      [5.2, 3.5, 1.5, 0.2],
                                      [5.2, 3.4, 1.4, 0.2],
                                      [4.7, 3.2, 1.6, 0.2],
                                      [4.8, 3.1, 1.6, 0.2],
                                      [5.4, 3.4, 1.5, 0.4],
                                      [5.2, 4.1, 1.5, 0.1],
                                      [5.5, 4.2, 1.4, 0.2],
                                      [4.9, 3.1, 1.5, 0.2],
                                      [5., 3.2, 1.2, 0.2],
                                      [5.5, 3.5, 1.3, 0.2],
                                      [4.9, 3.6, 1.4, 0.1],
                                      [4.4, 3., 1.3, 0.2],
                                      [5.1, 3.4, 1.5, 0.2],
                                      [5., 3.5, 1.3, 0.3],
                                      [4.5, 2.3, 1.3, 0.3],
                                      [4.4, 3.2, 1.3, 0.2],
                                      [5., 3.5, 1.6, 0.6],
                                      [5.1, 3.8, 1.9, 0.4],
                                      [4.8, 3., 1.4, 0.3],
                                      [5.1, 3.8, 1.6, 0.2],
                                      [4.6, 3.2, 1.4, 0.2],
                                      [5.3, 3.7, 1.5, 0.2],
                                      [5., 3.3, 1.4, 0.2],
                                      [7., 3.2, 4.7, 1.4],
                                      [6.4, 3.2, 4.5, 1.5],
                                      [6.9, 3.1, 4.9, 1.5],
                                      [5.5, 2.3, 4., 1.3],
                                      [6.5, 2.8, 4.6, 1.5],
                                      [5.7, 2.8, 4.5, 1.3],
                                      [6.3, 3.3, 4.7, 1.6],
                                      [4.9, 2.4, 3.3, 1.],
                                      [6.6, 2.9, 4.6, 1.3],
                                      [5.2, 2.7, 3.9, 1.4],
                                      [5., 2., 3.5, 1.],
                                      [5.9, 3., 4.2, 1.5],
                                      [6., 2.2, 4., 1.],
                                      [6.1, 2.9, 4.7, 1.4],
                                      [5.6, 2.9, 3.6, 1.3],
                                      [6.7, 3.1, 4.4, 1.4],
                                      [5.6, 3., 4.5, 1.5],
                                      [5.8, 2.7, 4.1, 1.],
                                      [6.2, 2.2, 4.5, 1.5],
                                      [5.6, 2.5, 3.9, 1.1],
                                      [5.9, 3.2, 4.8, 1.8],
                                      [6.1, 2.8, 4., 1.3],
                                      [6.3, 2.5, 4.9, 1.5],
                                      [6.1, 2.8, 4.7, 1.2],
                                      [6.4, 2.9, 4.3, 1.3],
                                      [6.6, 3., 4.4, 1.4],
                                      [6.8, 2.8, 4.8, 1.4],
                                      [6.7, 3., 5., 1.7],
                                      [6., 2.9, 4.5, 1.5],
                                      [5.7, 2.6, 3.5, 1.],
                                      [5.5, 2.4, 3.8, 1.1],
                                      [5.5, 2.4, 3.7, 1.],
                                      [5.8, 2.7, 3.9, 1.2],
                                      [6., 2.7, 5.1, 1.6],
                                      [5.4, 3., 4.5, 1.5],
                                      [6., 3.4, 4.5, 1.6],
                                      [6.7, 3.1, 4.7, 1.5],
                                      [6.3, 2.3, 4.4, 1.3],
                                      [5.6, 3., 4.1, 1.3],
                                      [5.5, 2.5, 4., 1.3],
                                      [5.5, 2.6, 4.4, 1.2],
                                      [6.1, 3., 4.6, 1.4],
                                      [5.8, 2.6, 4., 1.2],
                                      [5., 2.3, 3.3, 1.],
                                      [5.6, 2.7, 4.2, 1.3],
                                      [5.7, 3., 4.2, 1.2],
                                      [5.7, 2.9, 4.2, 1.3],
                                      [6.2, 2.9, 4.3, 1.3],
                                      [5.1, 2.5, 3., 1.1],
                                      [5.7, 2.8, 4.1, 1.3],
                                      [6.3, 3.3, 6., 2.5],
                                      [5.8, 2.7, 5.1, 1.9],
                                      [7.1, 3., 5.9, 2.1],
                                      [6.3, 2.9, 5.6, 1.8],
                                      [6.5, 3., 5.8, 2.2],
                                      [7.6, 3., 6.6, 2.1],
                                      [4.9, 2.5, 4.5, 1.7],
                                      [7.3, 2.9, 6.3, 1.8],
                                      [6.7, 2.5, 5.8, 1.8],
                                      [7.2, 3.6, 6.1, 2.5],
                                      [6.5, 3.2, 5.1, 2.],
                                      [6.4, 2.7, 5.3, 1.9],
                                      [6.8, 3., 5.5, 2.1],
                                      [5.7, 2.5, 5., 2.],
                                      [5.8, 2.8, 5.1, 2.4],
                                      [6.4, 3.2, 5.3, 2.3],
                                      [6.5, 3., 5.5, 1.8],
                                      [7.7, 3.8, 6.7, 2.2],
                                      [7.7, 2.6, 6.9, 2.3],
                                      [6., 2.2, 5., 1.5],
                                      [6.9, 3.2, 5.7, 2.3],
                                      [5.6, 2.8, 4.9, 2.],
                                      [7.7, 2.8, 6.7, 2.],
                                      [6.3, 2.7, 4.9, 1.8],
                                      [6.7, 3.3, 5.7, 2.1],
                                      [7.2, 3.2, 6., 1.8],
                                      [6.2, 2.8, 4.8, 1.8],
                                      [6.1, 3., 4.9, 1.8],
                                      [6.4, 2.8, 5.6, 2.1],
                                      [7.2, 3., 5.8, 1.6],
                                      [7.4, 2.8, 6.1, 1.9],
                                      [7.9, 3.8, 6.4, 2.],
                                      [6.4, 2.8, 5.6, 2.2],
                                      [6.3, 2.8, 5.1, 1.5],
                                      [6.1, 2.6, 5.6, 1.4],
                                      [7.7, 3., 6.1, 2.3],
                                      [6.3, 3.4, 5.6, 2.4],
                                      [6.4, 3.1, 5.5, 1.8],
                                      [6., 3., 4.8, 1.8],
                                      [6.9, 3.1, 5.4, 2.1],
                                      [6.7, 3.1, 5.6, 2.4],
                                      [6.9, 3.1, 5.1, 2.3],
                                      [5.8, 2.7, 5.1, 1.9],
                                      [6.8, 3.2, 5.9, 2.3],
                                      [6.7, 3.3, 5.7, 2.5],
                                      [6.7, 3., 5.2, 2.3],
                                      [6.3, 2.5, 5., 1.9],
                                      [6.5, 3., 5.2, 2.],
                                      [6.2, 3.4, 5.4, 2.3],
                                      [5.9, 3., 5.1, 1.8]]),
                            np.array(
                                [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                 2, 2, 2, 2, 2]))],

                          ]

from MyKNeighborsClassifier import MyKNeighborsClassifier

PART3_CLASSICAL_GRADE = 0.
test_count = 0.
for i, test_data in enumerate(part3_data):
    for j, classical_predict in enumerate(part3_classical_predict[i]):
        test_count += 1
        try:
            n_neighbors = test_data[0]
            X = test_data[1]
            y = test_data[2]
            norm = test_data[3]
            neigh = MyKNeighborsClassifier(n_neighbors=n_neighbors, method="classical", norm=norm)
            neigh.fit(X, y)
            answer = np.array(neigh.predict(classical_predict[0])).flatten()
            correct_answer = np.array(classical_predict[1]).flatten()
            if np.linalg.norm(answer - correct_answer) < EPSILON:
                PART3_CLASSICAL_GRADE += 1
            else:
                print "Wrong answer on data", i, "classical predict test", j, ":"
                print "Given answer:", answer
                print "Accepted answer:", correct_answer
        except Exception as e:
            print "Exception on data", i, "classical predict test", j, ":"
            print "Exception:", e
            traceback.print_exc()

if test_count != 0:
    PART3_CLASSICAL_GRADE = PART3_CLASSICAL_GRADE / test_count * 10

PART3_WEIGHTED_GRADE = 0.
test_count = 0.
for i, test_data in enumerate(part3_data):
    for j, weighted_predict in enumerate(part3_weighted_predict[i]):
        test_count += 1
        try:
            n_neighbors = test_data[0]
            X = test_data[1]
            y = test_data[2]
            norm = test_data[3]
            neigh = MyKNeighborsClassifier(n_neighbors=n_neighbors, method="weighted", norm=norm)
            neigh.fit(X, y)
            answer = np.array(neigh.predict(weighted_predict[0])).flatten()
            correct_answer = np.array(weighted_predict[1]).flatten()
            if np.linalg.norm(answer - correct_answer) < EPSILON:
                PART3_WEIGHTED_GRADE += 1
            else:
                print "Wrong answer on data", i, "weighted predict test", j, ":"
                print "Given answer:", answer
                print "Accepted answer:", correct_answer
        except Exception as e:
            print "Exception on data", i, "weighted predict test", j, ":"
            print "Exception:", e
            traceback.print_exc()

if test_count != 0:
    PART3_WEIGHTED_GRADE = PART3_WEIGHTED_GRADE / test_count * 10

PART3_VALIDITY_GRADE = 0.
test_count = 0.
for i, test_data in enumerate(part3_data):
    for j, validity_predict in enumerate(part3_validity_predict[i]):
        test_count += 1
        try:
            n_neighbors = test_data[0]
            X = test_data[1]
            y = test_data[2]
            norm = test_data[3]
            neigh = MyKNeighborsClassifier(n_neighbors=n_neighbors, method="validity", norm=norm)
            neigh.fit(X, y)
            answer = np.array(neigh.predict(validity_predict[0])).flatten()
            correct_answer = np.array(validity_predict[1]).flatten()
            if np.linalg.norm(answer - correct_answer) < EPSILON:
                PART3_VALIDITY_GRADE += 1
            else:
                print "Wrong answer on data", i, "validity predict test", j, ":"
                print "Given answer:", answer
                print "Accepted answer:", correct_answer
        except Exception as e:
            print "Exception on data", i, "validity predict test", j, ":"
            print "Exception:", e
            traceback.print_exc()

if test_count != 0:
    PART3_VALIDITY_GRADE = PART3_VALIDITY_GRADE / test_count * 10

print "Grades"
print "------"
print "part1_initialization:", PART1_INITIALIZATION_GRADE
print "part1_fit:", PART1_FIT_GRADE
print "part1_predict:", PART1_PREDICT_GRADE
print "part1_fit_predict:", PART1_FIT_PREDICT_GRADE

print "part2_pam:", PART2_PAM_GRADE
print "part2_clara:", PART2_CLARA_GRADE
print "part2_cluster:", PART2_CLUSTER_GRADE
print "part2_predict:", PART2_PREDICT_GRADE
print "part2_fit_predict:", PART2_FIT_PREDICT_GRADE

print "part3_classical:", PART3_CLASSICAL_GRADE
print "part3_weighted:", PART3_WEIGHTED_GRADE
print "part3_validity:", PART3_VALIDITY_GRADE
