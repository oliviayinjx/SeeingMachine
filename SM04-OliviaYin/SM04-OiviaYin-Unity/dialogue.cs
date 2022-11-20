using System.Collections;
using TMPro;
using UnityEngine;

public class dialogue : MonoBehaviour
{
    public TextMeshProUGUI textComponent;
    public string[] lines;
    public float textSpeed;
    public TMP_InputField displayField;

    public GameObject blackScreen;

    private string playerText;

    public string[] newlines;

    private int index;

    public bool touched;
    private bool tostart;
    private int counter = 3;
    private bool triggerNext;
    // Start is called before the first frame update
    void Start()
    {
        newlines = new string[6];

        playerText = PlayerPrefs.GetString("user_name");
    }

    // Update is called once per frame
    void Update()
    {
        //Debug.Log(playerText);

        if (touched)
        {
            touched = false;
            counter--;

            if(counter <= 0)
            {
                triggerNext = true;
                counter = 3;

            }
        }

        if (tostart)
        {
            if (textComponent.text == newlines[index] && triggerNext)
            {
                triggerNext = false;
                nextLine();
            }
            else if (textComponent.text != newlines[index])
            {
                StopAllCoroutines();
                textComponent.text = newlines[index];
            }
        }
    }

    void StartDialogue()
    {
        index = 0;
        StartCoroutine(Typeline());
    }

    IEnumerator Typeline()
    {
        foreach (char c in newlines[index].ToCharArray())
        {
            textComponent.text += c;
            //if(c == '-')
            //{
            //    textComponent.text += 't';
            //    Debug.Log("yes");
            //}
            //else
            //{
            //    textComponent.text += c;
            //}

            yield return new WaitForSeconds(textSpeed);
        }
    }

    void nextLine()
    {
        if(index< lines.Length - 1)
        {
            index++;
            textComponent.text = string.Empty;
            StartCoroutine(Typeline());
        }
        else
        {
            gameObject.SetActive(false);
        }
    }
    public void Create()
    {

        playerText = displayField.text;
        PlayerPrefs.SetString("user_name", playerText);
        PlayerPrefs.Save();

        for (int i = 0; i < lines.Length; i++)
        {
            newlines[i] = lines[i].Replace("[player]", playerText);
        }


        StartDialogue();
        textComponent.text = string.Empty;
        displayField.gameObject.SetActive(false);
        blackScreen.SetActive(false);

        tostart = true;
    }
}
